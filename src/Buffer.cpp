#include "Buffer.hpp"

namespace Reindeer
{
	namespace BufferUtils
	{
		#ifdef USE_GLES
		PFNGLMAPBUFFEROESPROC glMapBufferOES;
		PFNGLUNMAPBUFFEROESPROC glUnmapBufferOES;

		void initialize()
		{
			glMapBufferOES = (PFNGLMAPBUFFEROESPROC)swl_get_function("glMapBufferOES");
			glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC)swl_get_function("glUnmapBufferOES");
		}

		void *map(GLenum target)
		{
			return glMapBufferOES(target, GL_WRITE_ONLY_OES);
		}

		void unmap(GLenum target)
		{
			glUnmapBufferOES(target);
		}
		#else
		void initialize()
		{
		}
		void *map(GLenum target)
		{
			return glMapBuffer(target, GL_WRITE_ONLY);
		}

		void unmap(GLenum target)
		{
			glUnmapBuffer(target);
		}
		#endif

	};
};
