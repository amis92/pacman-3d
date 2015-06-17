#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include "Board.h"


class Game
{
public:
	static const unsigned int TexturesSize = 1;
	const double AmbientLightingValue = 0.5;
private:
	static GLuint textures[TexturesSize];
	static const Board board;
	static void SetAmbientLighting();
	static void PointLight(const float x, const float y, const float z,
		const float amb, const float diff, const float spec, const GLenum light);
	static void LoadTextures();
public:
	static void Init(int* argcp, char** argv);
	static void Display();
	static void RunMainLoop();
	static void Reshape(int width, int height);
	static void OnKeyboard(unsigned char key, int x, int y);
	static void OnSpecialKeys(int key, int x, int y);
};
