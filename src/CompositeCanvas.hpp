#pragma once
#include <string>
#include "../include/Reindeer/Canvas.hpp"
#include "../include/Reindeer/Layer.hpp"
#include "Common.hpp"
#include "Object.hpp"
#include "ContentSerializer.hpp"

namespace Reindeer
{
	template<class Source, class Mask, bool Conditional> struct ConditionalCanvas
	{
		typedef typename Mask::template Map<ObjectList<Source, Mask> > MaskMap;
		typedef typename Source::template Map<MaskMap> SourceMap;
		typedef typename SourceMap::Type Map;
		typedef SourceMap PrimaryMap;
		
		static ObjectList<Source, Mask> &get_list(Map &map, typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return MaskMap::resolve(SourceMap::resolve(map, source), mask);
		};
	};
	
	template<class Source, class Mask> struct ConditionalCanvas<Source, Mask, false>
	{
		typedef typename Source::template Map<ObjectList<Source, Mask> > SourceMap;
		typedef typename Mask::template Map<SourceMap> MaskMap;
		typedef typename MaskMap::Type Map;
		typedef MaskMap PrimaryMap;

		static ObjectList<Source, Mask> &get_list(Map &map, typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return SourceMap::resolve(MaskMap::resolve(map, mask), source);
		};
	};

	template<class Source, class Mask> class CompositeCanvas
	{
	private:
		typedef ConditionalCanvas<Source, Mask, Source::priority <= Mask::priority> Conditional;

		typename Conditional::Map map;

	public:
		struct StaticData 
		{
			GLuint program;
			GLuint scene_uniform;

			typename Source::State source_state;
			typename Mask::State mask_state;
		};
		
		static StaticData static_data;

		class Content:
			public Layer::Content
		{
			public:
				void render(ContentWalker &walker)
				{
					glUseProgram(static_data.program);

					glEnableVertexAttribArray(0);

					glUniform2f(static_data.scene_uniform, 400.0f, 240.0f);

					walker.read_object<Content>();

					Conditional::PrimaryMap::render(walker, static_data);
				}

				void deallocate(ContentWalker &walker)
				{
					walker.read_object<Content>();
					
					Conditional::PrimaryMap::deallocate(walker);
				}
		};

		CompositeCanvas(RegionAllocator &region) : map(region)
		{
		}
		
		void measure(ContentMeasurer &measurer)
		{
			measurer.count_objects<Content>(1);

			Conditional::PrimaryMap::measure(map, measurer);
			
			// TODO: Add a conditional for debug test

			measurer.count_objects<size_t>(1); // Magic
		}

		void serialize(ContentSerializer &serializer)
		{
			serializer.write_object<Content>();
			
			Conditional::PrimaryMap::serialize(map, serializer);

			// TODO: Add a conditional for debug test

			size_t &magic = serializer.write_object<size_t>();

			magic = 0xBEEF;
		}

		ObjectList<Source, Mask> &get_list(typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return Conditional::get_list(map, source, mask);
		};

		static void initialize(size_t width, size_t height)
		{
			std::string vertex_shader = "precision highp float;";
				
			vertex_shader += Source::vertex_code;
			vertex_shader += Mask::vertex_code;

			vertex_shader += "uniform vec2 scene;\
				attribute vec2 point;\
				void main(void)\
				{\
					gl_Position = vec4(point.x / scene.x - 1.0, 1.0 - point.y / scene.y, 0.0, 1.0);";

			vertex_shader += Source::vertex_main;
			vertex_shader += Mask::vertex_main;

			vertex_shader += "}";
			
			std::string fragment_shader = "precision highp float;";
				
			fragment_shader += Source::fragment_code;
			fragment_shader += Mask::fragment_code;

			fragment_shader += "\
				void main(void)\
				{";
			
			fragment_shader += Source::fragment_main;
			fragment_shader += Mask::fragment_main;

			fragment_shader += "}";

			static_data.program = glCreateProgram();
			
			gluCompileShader(static_data.program, GL_VERTEX_SHADER, vertex_shader.c_str());
			gluCompileShader(static_data.program, GL_FRAGMENT_SHADER, fragment_shader.c_str());
			
			glBindAttribLocation(static_data.program, 0, "point");

			gluLinkProgram(static_data.program);
			
			Source::initialize_state(static_data.source_state, static_data.program);
			Mask::initialize_state(static_data.mask_state, static_data.program);
			
			static_data.scene_uniform = glGetUniformLocation(static_data.program, "scene");

			glUseProgram(static_data.program);

			glUniform2f(static_data.scene_uniform, width / 2.0f, height / 2.0f);
		}
	};
	
	template<class Source, class Mask> typename CompositeCanvas<Source, Mask>::StaticData CompositeCanvas<Source, Mask>::static_data;
};
