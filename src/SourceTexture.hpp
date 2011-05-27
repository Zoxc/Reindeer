#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class SourceTexture
	{
	public:
		const static Priority priority = PriorityTexture;

		template<class Inner> struct Map
		{
			typedef typename Reindeer::Map<Texture *, Inner> Type;
		};
	};
};
