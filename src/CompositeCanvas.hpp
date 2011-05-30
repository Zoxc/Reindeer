#pragma once
#include <string>
#include "../include/Reindeer/Canvas.hpp"
#include "Common.hpp"
#include "Object.hpp"

namespace Reindeer
{
	template<class Source, class Mask, bool Conditional> struct ConditionalCanvas
	{
		typedef typename Mask::template Map<ObjectList<Source, Mask> > MaskMap;
		typedef typename Source::template Map<typename MaskMap::Type> SourceMap;
		typedef typename SourceMap::Type Map;
		
		static ObjectList<Source, Mask> &get_list(Map &map, typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return MaskMap::resolve(SourceMap::resolve(map, source), mask);
		};
	};
	
	template<class Source, class Mask> struct ConditionalCanvas<Source, Mask, false>
	{
		typedef typename Source::template Map<ObjectList<Source, Mask> > SourceMap;
		typedef typename Mask::template Map<typename SourceMap::Type> MaskMap;
		typedef typename MaskMap::Type Map;

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
		CompositeCanvas(RegionAllocator &region) : map(region)
		{
		}

		ObjectList<Source, Mask> &get_list(typename Source::ArgumentType source, typename Mask::ArgumentType mask)
		{
			return Conditional::get_list(map, source, mask);
		};

		static GLuint program;
		static GLuint scene_uniform;
		
		static typename Source::State source_state;
		static typename Mask::State mask_state;

		static void initialize()
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

			program = glCreateProgram();
			
			gluCompileShader(program, GL_VERTEX_SHADER, vertex_shader.c_str());
			gluCompileShader(program, GL_FRAGMENT_SHADER, fragment_shader.c_str());
			
			gluLinkProgram(program);
			
			Source::initialize_state(source_state, program);
			Mask::initialize_state(mask_state, program);
			
			scene_uniform = glGetUniformLocation(program, "scene");
		}
	};
	
	template<class Source, class Mask> GLuint CompositeCanvas<Source, Mask>::program;
	template<class Source, class Mask> GLuint CompositeCanvas<Source, Mask>::scene_uniform;

	template<class Source, class Mask> typename Source::State CompositeCanvas<Source, Mask>::source_state;
	template<class Source, class Mask> typename Mask::State CompositeCanvas<Source, Mask>::mask_state;
};
