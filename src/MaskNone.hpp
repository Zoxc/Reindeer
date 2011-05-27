#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskNone
	{
	public:
		typedef void *ArgumentType;

		const static Priority priority = PriorityNone;

		template<class Inner> struct Map
		{
			typedef Inner Type;

			static Inner &resolve(Inner &inner, void *argument)
			{
				return inner;
			}
		};
	};
};
