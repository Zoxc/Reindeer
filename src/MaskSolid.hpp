#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskSolid
	{
	public:
		typedef color_t ArgumentType;

		const static Priority priority = PriorityUniform;

		const static Mask::Type type = Mask::Solid;
		
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
			typedef typename Reindeer::Map<alpha_t, typename Inner::Type> Type;
			
			static typename Inner::Type &resolve(Type &map, alpha_t alpha)
			{
				return map.get_create(alpha);
			}

			static void measure(Type &map, ContentMeasurer &measurer)
			{
			}

			static void serialize(Type &map, ContentSerializer &serializer)
			{
			}
		};
	};
};
