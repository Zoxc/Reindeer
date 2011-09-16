#pragma once
#include <malloc.h>

#ifdef USE_GLES
	#include <GLES2/gl2.h>
	#define glClearDepth glClearDepthf
#else
	#include <GLee.h>

	// Remove X11 macro if it was included
	#undef None
#endif

bool gluCompileShader(GLuint program, GLenum type, const char *source);
bool gluLinkProgram(GLuint program);
void gluRaiseErrors();
