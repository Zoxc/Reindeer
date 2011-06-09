#pragma once
#include <Prelude/Region.hpp>
#include <Prelude/List.hpp>
#include "Color.hpp"

namespace Reindeer
{
	typedef Prelude::Region<> RegionAllocator;

	namespace Operator
	{
		enum Type
		{
			Over,
			Count
		};
	};
	
	namespace Source
	{
		enum Type
		{
			Solid,
			Texture,
			Count
		};
	};

	namespace Mask
	{
		enum Type
		{
			None,
			Solid,
			Texture,
			Count
		};
	};

	class Texture;

	struct CanvasFriend;
	class LayerContext;
	
	class ContentMeasurer;
	class ContentSerializer;
	
	class Canvas
	{
	private:
		LayerContext &context;
		RegionAllocator &region;

		Source::Type source_type;
		Mask::Type mask_type;
		
		Texture *source_texture;
		Texture *mask_texture;
		
		color_t source_color;
		color_t mask_color;
		
		Prelude::ListEntry<Canvas> entry;
		
		void measure(ContentMeasurer &measurer);
		void serialize(ContentSerializer &serializer);

		void *canvas_map[Source::Count * Mask::Count];

	public:
		Canvas(LayerContext &context);
		
		void set_source(color_t color);
		void set_source(Texture *texture);
		
		void set_mask(color_t color);
		void set_mask(Texture *texture);
		void clear_mask();

		void rect(int x, int y, int width, int height);
		
		friend struct CanvasFriend;
		friend class LayerContext;
		
	};
};
