#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class SourceSolid
	{
	public:
		typedef color_t ArgumentType;

		const static Priority priority = PriorityUniform;
		
		const static char *vertex_code;
		const static char *vertex_main;

		const static char *fragment_code;
		const static char *fragment_main;
		
		struct ObjectData
		{
			ObjectData(color_t color) {}
		};
		
		struct State {
			GLuint color_uniform;
		};
		
		static void initialize_state(State &state, GLuint program)
		{
			state.color_uniform = glGetUniformLocation(program, "source_color");
		};

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
