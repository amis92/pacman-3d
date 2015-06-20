#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include "imageloader.h"

class TextureLoader
{
	/* Loads bitmap from file with just pixels.
	 */
	static Image* LoadRaw(const char* filename, int width, int height);

	/* Setups and returns OpenGL texture identifier.
	*/
	static GLuint BindTex();
public:
	/* Loads bitmap from bmp file, converts into texture mipmap and returns
	* OpenlGL texture identifier.
	*/
	static GLuint LoadBmpTex(const char* filename);

	/* Loads bitmap from file with just pixels, converts into texture mipmap and returns
	 * OpenlGL texture identifier.
	 */
	static GLuint LoadRawTex(const char* filename, int width, int height);
};
