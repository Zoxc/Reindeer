#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskNone
	{
	public:
		typedef void *ArgumentType;

		const static Priority priority = PriorityNone;
		
		const static char *vertex_code;
		const static char *vertex_main;

		const static char *fragment_code;
		const static char *fragment_main;
		
		struct ObjectData
		{
			ObjectData(void *argument) {}
		};

		struct State {};

		static void initialize_state(State &state, GLuint program) {};

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
