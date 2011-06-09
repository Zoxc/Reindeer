#pragma once
#include <Prelude/Region.hpp>
#include <Prelude/List.hpp>
#include "Canvas.hpp"

namespace Reindeer
{
	class Layer;

	class ContentMeasurer;
	class ContentSerializer;

	class LayerContext
	{
	private:
		RegionAllocator region;

	public:
		typedef Prelude::List<Canvas> CanvasList;
		
		friend class Canvas;

		Layer *render();

		CanvasList layers;

		Canvas &add_layer();
	};
};
