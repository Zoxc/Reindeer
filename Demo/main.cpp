#include <Prelude/Region.hpp>
#include <Reindeer/Reindeer.hpp>
#include <Reindeer/Canvas.hpp>
#include <swl.h>
#include <stdio.h>

using namespace Prelude;

Region<> region;

Reindeer::Canvas canvas(region);

const int width = 800;
const int height = 480;

int main()
{
	enum swl_result result = swl_init("CubeLand", width, height);

	if(result != SWLR_OK)
	{
		printf("Unable to setup window... %d", result);
		return -1;
	}

	Reindeer::initialize(width, height);
	
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
		
		swl_swap();
	}

	quit:
	swl_quit();

	return 0;
}