#pragma once
#include "Common.hpp"

namespace Reindeer
{
	class MaskTexture
	{
	public:
		typedef Texture *ArgumentType;
		
		const static Priority priority = PriorityTexture;

		const static Mask::Type type = Mask::Texture;
		
		const static char *vertex_code;
		const static char *vertex_main;

		const static char *fragment_code;
		const static char *fragment_main;
		
		struct ObjectData
		{
			ObjectData(Texture *texture) {}
		};
		
		struct State {};
		
		static void initialize_state(State &state, GLuint program) {};

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
