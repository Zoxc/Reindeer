#include "ContentSerializer.hpp"
#include "Common.hpp"
#include "../include/Reindeer/LayerContext.hpp"
#include "../include/Reindeer/Layer.hpp"

namespace Reindeer
{
	Layer *LayerContext::render()
	{
		ContentMeasurer measurer;

		for(auto i = layers.begin(); i != layers.end(); ++i)
			(*i)->measure(measurer);

		void *memory = std::malloc(measurer.get_size());
			
		ContentSerializer serializer(memory);

		for(auto i = layers.begin(); i != layers.end(); ++i)
			(*i)->serialize(serializer);

		assert((size_t)(serializer.get_position() - (char *)memory) == measurer.get_size());
		
		return new Layer(memory, measurer.get_size());
	}

	Canvas &LayerContext::add_layer()
	{
		Canvas *layer = new (region) Canvas(*this);
		layers.append(layer);
		return *layer;
	}
};
