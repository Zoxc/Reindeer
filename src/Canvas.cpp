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
		template<template<typename> class T, typename Arg> static void source_dispatch(Canvas &canvas, Arg arg)
		{
			switch(canvas.source_type)
			{
			case Source::Solid:
				return T<SourceSolid>::func(canvas, canvas.source_color, arg);
				
			case Source::Texture:
				return T<SourceTexture>::func(canvas, canvas.source_texture, arg);

			default:
				assert(0 && "Unknown source type");
			};
		}

		template<template<typename, typename> class T, typename SourceCanvas, typename Arg1, typename Arg2> static void mask_dispatch(Canvas &canvas, Arg1 arg1, Arg2 arg2)
		{
			switch(canvas.mask_type)
			{
			case Mask::None:
				return T<SourceCanvas, MaskNone>::func(canvas, nullptr, arg1, arg2);

			case Mask::Solid:
				return T<SourceCanvas, MaskSolid>::func(canvas, canvas.mask_color, arg1, arg2);
				
			case Mask::Texture:
				return T<SourceCanvas, MaskTexture>::func(canvas, canvas.mask_texture, arg1, arg2);

			default:
				assert(0 && "Unknown mask type");
			};
		}

		template<class SourceCanvas, class MaskCanvas> static CompositeCanvas<SourceCanvas, MaskCanvas> & get_composite_canvas(Canvas &canvas)
		{
			size_t index = canvas.mask_type * Mask::Count + canvas.source_type;

			auto result = (CompositeCanvas<SourceCanvas, MaskCanvas> *)canvas.canvas_map[index];

			if(!result)
				result = new (canvas.region.allocate(sizeof(CompositeCanvas<SourceCanvas, MaskCanvas>))) CompositeCanvas<SourceCanvas, MaskCanvas>(canvas.region);

			return *result;
		}
	};
	
	template<class SourceCanvas, class MaskCanvas> struct MaskDestionation
	{
		static void func(Canvas &canvas, typename MaskCanvas::ArgumentType mask, typename SourceCanvas::ArgumentType source, Rect &rect)
		{
			auto composite_canvas = CanvasFriend::get_composite_canvas<SourceCanvas, MaskCanvas>(canvas);

			auto object_list = composite_canvas.get_list(source, mask);


		}
	};

	template<class SourceCanvas> struct SourceDestination
	{
		static void func(Canvas &canvas, typename SourceCanvas::ArgumentType source, Rect &rect)
		{
			CanvasFriend::mask_dispatch<MaskDestionation, SourceCanvas, typename SourceCanvas::ArgumentType, Rect &>(canvas, source, rect);
		}
	};
	
	void Canvas::set_source(color_t color)
	{
		source_type = Source::Solid;
	}

	void Canvas::set_source(Texture *texture)
	{
		source_type = Source::Texture;
	}

	void Canvas::set_mask(color_t color)
	{
		mask_type = Mask::Solid;
	}

	void Canvas::set_mask(Texture *texture)
	{
		mask_type = Mask::Texture;
	}

	void Canvas::clear_mask()
	{
		mask_type = Mask::None;
	}
	
	void Canvas::rect(int x, int y, int width, int height)
	{
		Rect rect;

		rect.x = x;
		rect.y = y;
		rect.width = width;
		rect.height = height;

		CanvasFriend::source_dispatch<SourceDestination, Rect &>(*this, rect);
	}
};
