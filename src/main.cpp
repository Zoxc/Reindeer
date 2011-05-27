#include <Prelude/List.hpp>
#include <Prelude/Internal/ChunkList.hpp>
#include <Prelude/Allocator.hpp>
#include <Prelude/Region.hpp>
#include "../include/Reindeer/Canvas.hpp"

using namespace Prelude;

Region<> region;

Reindeer::Canvas canvas(region);

int main()
{
		return 0;
}