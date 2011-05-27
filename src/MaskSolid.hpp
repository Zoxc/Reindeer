#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskSolid
	{
	public:
		typedef color_t ArgumentType;

		const static Priority priority = PriorityUniform;

		template<class Inner> struct Map
		{
			typedef typename Reindeer::Map<alpha_t, Inner> Type;
			
			static Inner &resolve(Type map, alpha_t alpha)
			{
				return map.get_create(alpha);
			}
		};
	};
};
