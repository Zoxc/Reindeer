#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskTexture
	{
	public:
		typedef Texture *ArgumentType;
		
		const static Priority priority = PriorityTexture;

		template<class Inner> struct Map
		{
			typedef typename Reindeer::Map<Texture *, Inner> Type;
			
			static Inner &resolve(Type map, Texture *texture)
			{
				return map.get_create(texture);
			}
		};
	};
};
