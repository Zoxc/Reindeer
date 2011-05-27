#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class SourceSolid
	{
	public:
		typedef color_t ArgumentType;

		const static Priority priority = PriorityUniform;

		template<class Inner> struct Map
		{
			typedef typename Reindeer::Map<color_t, Inner> Type;
			
			static Inner &resolve(Type map, color_t color)
			{
				return map.get_create(color);
			}
		};
	};
};
