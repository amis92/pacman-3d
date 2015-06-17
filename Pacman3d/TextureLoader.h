#pragma once

#include <Windows.h>
#include <GL/gl.h>

class TextureLoader
{
public:
	/* Loads bitmap from file, converts into texture mipmap and returns
	 * OpenlGL identifier under which it is remembered.
	 */
	static GLuint LoadRawTex(const char* filename, int width, int height);
};
