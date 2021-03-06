#include <Prelude/Region.hpp>
#include <Reindeer/Reindeer.hpp>
#include <Reindeer/Canvas.hpp>
#include <swl.h>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace Prelude;

const int width = 800;
const int height = 480;

int main()
{
	enum swl_result result = swl_init("Reindeer Demo", width, height);

	if(result != SWLR_OK)
	{
		printf("Unable to setup window... %d", result);
		return -1;
	}

	Reindeer::initialize(width, height);
	
	Reindeer::LayerContext context;

	auto &canvas = context.add_layer();
	
	canvas.set_source(0xFF0000FF);
	canvas.clear_mask();
	
	canvas.rect(10, 10, 20, 20);

	auto layer = context.render();

	struct swl_event event;

	while(1)
	{
		while(swl_query(&event))
		{
			switch(event.type)
			{
			case SWLE_QUIT:
				goto quit;

			default:
				break;
			};
		}
		
		layer->render();

		swl_swap();
	}

	quit:
	swl_quit();

	return 0;
}