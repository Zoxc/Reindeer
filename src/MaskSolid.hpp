#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskSolid
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
		
		struct State {};
		
		static void initialize_state(State &state, GLuint program) {};

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
