#include "TextureLoader.h"

#include <stdio.h>
#include <GL/glu.h>
#include "imageloader.h"

Image* TextureLoader::LoadRaw(const char* filename, int width, int height)
{
	FILE* file = nullptr;

	// open texture data
	fopen_s(&file, filename, "rb");
	if (file == nullptr) return nullptr;

	// allocate buffer
	auto pixels = new char[width * height * 4];

	// read texture data
	fread(pixels, width * height * 4, 1, file);
	fclose(file);
	return new Image(pixels, width, height);
}

GLuint TextureLoader::BindTex()
{
	GLuint textureId;

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

	return textureId;
}

GLuint TextureLoader::LoadBmpTex(const char* filename)
{
	auto* img = loadBMP(filename);
	auto textureId = BindTex();
	// build our texture mipmaps
	auto result = gluBuild2DMipmaps(GL_TEXTURE_2D, 4, img->width, img->height, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
	delete img;
	return textureId;
}

GLuint TextureLoader::LoadRawTex(const char* filename, int width, int height)
{
	auto* img = LoadRaw(filename, width, height);
	auto textureId = BindTex();
	// build our texture mipmaps
	auto result = gluBuild2DMipmaps(GL_TEXTURE_2D, 4, img->width, img->height, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	delete img;
	return textureId;
}
