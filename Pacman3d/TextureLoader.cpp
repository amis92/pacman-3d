#include "TextureLoader.h"

#include <stdio.h>
#include <GL/glu.h>

GLuint TextureLoader::LoadRawTex(const char* filename, int width, int height)
{
	GLuint textureId;
	unsigned char* data;
	FILE* file = nullptr;

	// open texture data
	fopen_s(&file, filename, "rb");
	if (file == nullptr) return 0;

	// allocate buffer
	data = static_cast<unsigned char*>(malloc(width * height * 4));

	// read texture data
	fread(data, width * height * 4, 1, file);
	fclose(file);

	// allocate a texture name
	glGenTextures(1, &textureId);

	// select our current texture
	glBindTexture(GL_TEXTURE_2D, textureId);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	return textureId;
}