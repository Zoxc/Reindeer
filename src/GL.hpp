#pragma once
#if defined(_WIN32) && !defined(NOMINMAX)
	#define NOMINMAX
#endif

#include <malloc.h>

#ifdef USE_GLES
	#include <GLES2/gl2.h>
	#define glClearDepth glClearDepthf
#else
	#include <GLee.h>
#endif

bool gluCompileShader(GLuint program, GLenum type, const char *source);
bool gluLinkProgram(GLuint program);
