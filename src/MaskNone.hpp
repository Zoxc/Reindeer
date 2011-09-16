#pragma once
#include "Common.hpp"
#include "ContentSerializer.hpp"

namespace Reindeer
{
	class MaskNone
	{
	public:
		typedef void *ArgumentType;
		
		const static Priority priority = PriorityNone;

		const static Mask::Type type = Mask::None;
		
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
			typedef typename Inner::Type Type;

			static typename Inner::Type &resolve(typename Inner::Type &inner, void *argument)
			{
				return inner;
			}

			static void measure(Type &inner, ContentMeasurer &measurer)
			{
				Inner::measure(inner, measurer);
			}

			static void serialize(Type &inner, ContentSerializer &serializer)
			{
				Inner::serialize(inner, serializer);
			}
			
			template<class T> static void render(ContentWalker &walker, T &static_data)
			{
				Inner::render(walker, static_data);
			}
			
			static void deallocate(ContentWalker &walker)
			{
				Inner::deallocate(walker);
			}
		};
	};
};
