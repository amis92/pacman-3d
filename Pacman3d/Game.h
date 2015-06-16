#pragma once

#include <Windows.h>
#include <GL/gl.h>


class Game
{
	static void SetAmbientLighting();
	static void PointLight(const float x, const float y, const float z,
		const float amb, const float diff, const float spec, const GLenum light);
public:
	const double AmbientLightingValue = 0.5;
	static void Init(int* argcp, char** argv);
	static void Display();
	static void RunMainLoop();
	static void Reshape(int width, int height);
	static void OnKeyboard(unsigned char key, int x, int y);
	static void OnSpecialKeys(int key, int x, int y);
};
