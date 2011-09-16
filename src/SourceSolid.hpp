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
			typedef SourceSolid::State State;
			
			static typename Inner::Type &resolve(Type& map, color_t color)
			{
				return map.get_create(color);
			}
			
			//TODO: Remove workaround for VS bug

			static void measure_inner(typename Inner::Type &value, ContentMeasurer &measurer)
			{
				Inner::measure(value, measurer);
			}

			static void serialize_inner(typename Inner::Type &value, ContentSerializer &serializer)
			{
				Inner::serialize(value, serializer);
			}

			static void measure(Type &map, ContentMeasurer &measurer)
			{
				measurer.count_map<color_t>(map, [&](color_t key, typename Inner::Type *value) {
						REINDEER_SCOPE(Map) measure_inner(*value, measurer);
				});
			}

			static void serialize(Type &map, ContentSerializer &serializer)
			{
				serializer.write_map(map, [&](color_t key, typename Inner::Type *value) {
						color_t &color = serializer.write_object<color_t>();

						color = key;

						REINDEER_SCOPE(Map) serialize_inner(*value, serializer);
				});
			}
			
			static uint8_t color_red_component(color_t color)
			{
				return (color >> 24) & 0xFF;
			}

			static uint8_t color_green_component(color_t color)
			{
				return (color >> 16) & 0xFF;
			}

			static uint8_t color_blue_component(color_t color)
			{
				return (color >> 8) & 0xFF;
			}

			static uint8_t color_alpha_component(color_t color)
			{
				return color & 0xFF;
			}

			template<class T> static void render(ContentWalker &walker, T &static_data)
			{
				for(auto i = walker.read_list<color_t>(); i.get_next();)
				{
					glUniform4f(static_data.source_state.color_uniform, color_red_component(i()) / 255.0f, color_green_component(i()) / 255.0f, color_blue_component(i()) / 255.0f, color_alpha_component(i()) / 255.0f);
					
					Inner::render(walker, static_data);
				}
			}
			
			static void deallocate(ContentWalker &walker)
			{
			}
		};
	};
};
