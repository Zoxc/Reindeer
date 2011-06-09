#pragma once
#include "../include/Reindeer/Canvas.hpp"
#include "CompositeCanvas.hpp"
#include "SourceSolid.hpp"
#include "SourceTexture.hpp"
#include "MaskNone.hpp"
#include "MaskSolid.hpp"
#include "MaskTexture.hpp"

namespace Reindeer
{
	struct CanvasFriend
	{
		template<class Source> static typename Source::ArgumentType get_source_state(Canvas &canvas);
		
		template<> static typename SourceSolid::ArgumentType get_source_state<SourceSolid>(Canvas &canvas)
		{
			return canvas.source_color;
		}

		template<> static typename SourceTexture::ArgumentType get_source_state<SourceTexture>(Canvas &canvas)
		{
			return canvas.source_texture;
		}

		template<class Mask> static typename Mask::ArgumentType get_mask_state(Canvas &canvas);
		
		template<> static typename MaskNone::ArgumentType get_mask_state<MaskNone>(Canvas &canvas)
		{
			return nullptr;
		}
		
		template<> static typename MaskSolid::ArgumentType get_mask_state<MaskSolid>(Canvas &canvas)
		{
			return canvas.mask_color;
		}

		template<> static typename MaskTexture::ArgumentType get_mask_state<MaskTexture>(Canvas &canvas)
		{
			return canvas.mask_texture;
		}

		static Mask::Type get_mask_type(Canvas &canvas)
		{
			return canvas.mask_type;
		}
		
		static RegionAllocator &get_region(Canvas &canvas)
		{
			return canvas.region;
		}

		template<template<typename> class T, typename Arg1, typename Arg2> static void source_dispatch(Source::Type source, Arg1 arg1, Arg2 arg2)
		{
			switch(source)
			{
			case Source::Solid:
				return T<SourceSolid>::func(arg1, arg2);
				
			case Source::Texture:
				return T<SourceTexture>::func(arg1, arg2);

			default:
				assert(0 && "Unknown source type");
			};
		}

		template<template<typename, typename> class T, typename Source, typename Arg1, typename Arg2> static void mask_dispatch(Mask::Type mask, Arg1 arg1, Arg2 arg2)
		{
			switch(mask)
			{
			case Mask::None:
				return T<Source, MaskNone>::func(arg1, arg2);

			case Mask::Solid:
				return T<Source, MaskSolid>::func(arg1, arg2);
				
			case Mask::Texture:
				return T<Source, MaskTexture>::func(arg1, arg2);

			default:
				assert(0 && "Unknown mask type");
			};
		}

		template<class Source, class Mask> static CompositeCanvas<Source, Mask> & get_composite_canvas(Canvas &canvas)
		{
			size_t index = canvas.mask_type * Reindeer::Mask::Count + canvas.source_type;

			auto result = (CompositeCanvas<Source, Mask> *)canvas.canvas_map[index];

			if(!result)
			{
				result = new (canvas.region) CompositeCanvas<Source, Mask>(canvas.region);
				canvas.canvas_map[index] = (void *)result;
			}

			return *result;
		}
	};
};
