#include "CanvasFriend.hpp"
#include "../include/Reindeer/LayerContext.hpp"

namespace Reindeer
{
	template<class Source, class Mask> struct MaskDestionation
	{
		static void func(Canvas &canvas, Rect &rect)
		{
			auto &composite_canvas = *CanvasFriend::get_composite_canvas<Source, Mask, true>(canvas);
			
			typename Source::ArgumentType source = CanvasFriend::get_source_state<Source>(canvas);
			typename Mask::ArgumentType mask = CanvasFriend::get_mask_state<Mask>(canvas);

			auto &object_list = composite_canvas.get_list(source, mask);

			auto object = new (CanvasFriend::get_region(canvas)) Object<Source, Mask>(source, mask, rect);

			object_list.append(object);
		}
	};

	template<class Source> struct SourceDestination
	{
		static void func(Canvas &canvas, Rect &rect)
		{
			CanvasFriend::mask_dispatch<MaskDestionation, Source, Canvas &, Rect &>(CanvasFriend::get_mask_type(canvas), canvas, rect);
		}
	};

	Canvas::Canvas(LayerContext &context) : context(context), region(context.region)
	{
		std::memset(canvas_map, 0, sizeof(void *) * Source::Count * Mask::Count);
	}
	
	void Canvas::set_source(color_t color)
	{
		source_type = Source::Solid;
		source_color = color;
	}

	void Canvas::set_source(Texture *texture)
	{
		source_type = Source::Texture;
	}

	void Canvas::set_mask(color_t color)
	{
		mask_type = Mask::Solid;
		mask_color = color;
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

		CanvasFriend::source_dispatch<SourceDestination, Canvas &, Rect &>(source_type, *this, rect);
	}
	
	template<class Source, class Mask> struct MeasureMaskDestionation
	{
		static void func(Canvas &canvas, ContentMeasurer &measurer)
		{
			auto composite_canvas = CanvasFriend::get_composite_canvas<Source, Mask, false>(canvas);

			if(composite_canvas)
				composite_canvas->measure(measurer);
		}
	};

	template<class Source> struct MeasureSourceDestination
	{
		static void func(Canvas &canvas, ContentMeasurer &measurer)
		{
			for(size_t mask = Mask::None; mask < Mask::Count; ++mask)
				CanvasFriend::mask_dispatch<MeasureMaskDestionation, Source, Canvas &, ContentMeasurer &>((Mask::Type)mask, canvas, measurer);
		}
	};
	
	void Canvas::measure(ContentMeasurer &measurer)
	{
		for(size_t source = Source::Solid; source < Source::Count; ++source)
			CanvasFriend::source_dispatch<MeasureSourceDestination, Canvas &, ContentMeasurer &>((Source::Type)source, *this, measurer);
	}
	
	template<class Source, class Mask> struct SerializeMaskDestionation
	{
		static void func(Canvas &canvas, ContentSerializer &serializer)
		{
			auto composite_canvas = CanvasFriend::get_composite_canvas<Source, Mask, false>(canvas);
			
			if(composite_canvas)
				composite_canvas->serialize(serializer);
		}
	};

	template<class Source> struct SerializeSourceDestination
	{
		static void func(Canvas &canvas, ContentSerializer &serializer)
		{
			for(size_t mask = Mask::None; mask < Mask::Count; ++mask)
				CanvasFriend::mask_dispatch<SerializeMaskDestionation, Source, Canvas &, ContentSerializer &>((Mask::Type)mask, canvas, serializer);
		}
	};
	
	void Canvas::serialize(ContentSerializer &serializer)
	{
		for(size_t source = Source::Solid; source < Source::Count; ++source)
			CanvasFriend::source_dispatch<SerializeSourceDestination, Canvas &, ContentSerializer &>((Source::Type)source, *this, serializer);
	}
};
