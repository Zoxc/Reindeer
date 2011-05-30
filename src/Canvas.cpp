#include "CanvasFriend.hpp"

namespace Reindeer
{
	template<class Source, class Mask> struct MaskDestionation
	{
		static void func(Canvas &canvas, Rect &rect)
		{
			auto composite_canvas = CanvasFriend::get_composite_canvas<Source, Mask>(canvas);
			
			Source::ArgumentType source = CanvasFriend::get_source_state<Source>(canvas);
			Mask::ArgumentType mask = CanvasFriend::get_mask_state<Mask>(canvas);

			auto object_list = composite_canvas.get_list(source, mask);

			auto object = new (canvas.region) Object<Source, Mask>(source, mask, rect);

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

		CanvasFriend::source_dispatch<SourceDestination, Canvas &, Rect &>(source_type, *this, rect);
	}
};
