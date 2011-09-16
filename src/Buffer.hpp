#pragma once
#include "GL.hpp"

namespace Reindeer
{
	namespace BufferUtils
	{
		void *map(GLenum target);
		void unmap(GLenum target);
		void initialize();
	};

	template<GLenum target, class T> class Buffer
	{
	private:
		GLuint handle;

	public:
		~Buffer()
		{
			glDeleteBuffers(1, &handle);
		}
		
		T *setup(GLsizeiptr size)
		{
			glGenBuffers(1, &handle);
			bind();
			glBufferData(target, size * sizeof(T), 0, GL_STATIC_DRAW);
			return (T *)BufferUtils::map(target);
		}

		void bind()
		{
			glBindBuffer(target, handle);
		}

		T *map()
		{
			bind();
			return (T *)BufferUtils::map(target);
		}

		void unmap()
		{
			bind();
			BufferUtils::unmap(target);
		}
	};
};
