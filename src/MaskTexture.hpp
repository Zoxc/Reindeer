#pragma once
#include "Common.hpp"
#include "ContentSerializer.hpp"

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
			typedef typename Reindeer::Map<Texture *, typename Inner::Type> Type;
			
			static typename Inner::Type &resolve(Type &map, Texture *texture)
			{
				return map.get_create(texture);
			}

			static void measure(Type &map, ContentMeasurer &measurer)
			{
			}

			static void serialize(Type &map, ContentSerializer &serializer)
			{
			}
			
			template<class T> static void render(ContentWalker &walker, T &static_data)
			{
			}
			
			static void deallocate(ContentWalker &walker)
			{
			}
		};
	};
};
