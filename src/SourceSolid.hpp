#pragma once
#include "Common.hpp"
#include "ContentSerializer.hpp"

namespace Reindeer
{
	class SourceSolid
	{
	public:
		typedef color_t ArgumentType;

		const static Priority priority = PriorityUniform;

		const static Source::Type type = Source::Solid;
		
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
			typedef typename Reindeer::Map<color_t, typename Inner::Type> Type;
			
			static typename Inner::Type &resolve(Type& map, color_t color)
			{
				return map.get_create(color);
			}
			
			static void measure(Type &map, ContentMeasurer &measurer)
			{
				measurer.count_map<color_t>(map, [&](color_t key, typename Inner::Type &value) {
						Inner::measure(value, measurer);
				});
			}

			static void serialize(Type &map, ContentSerializer &serializer)
			{
				serializer.write_map([&](color_t key, typename Inner::Type &value) {
						color_t &color = serializer.write_object<color_t>();

						color = key;

						Inner::serialize(value, serializer);
				});
			}
		};
	};
};
