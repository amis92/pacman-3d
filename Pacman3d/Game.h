#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include <GL/gl.h>
#include "Board.h"


class Game
{
public:
	static const unsigned int TexturesSize = 4;
	static const int TestTextureIndex = 0;
	static const int FloorTextureIndex = 1;
	static const int WallTextureIndex = 2;
	static const int WallFloorTextureIndex = 3;
	const double AmbientLightingValue = 0.5;
	static const double maxCameraArc;
private:
	static double cameraArc;
	static double cameraRadius;
	static GLuint textures[TexturesSize];
	static Board board;
	static void SetAmbientLighting();
	static void PointLight(const float x, const float y, const float z,
	                       const float amb, const float diff, const float spec, const GLenum light);
	static void LoadTextures();
	static void PositionCamera();
	static void RecalculateCameraArc(int frameNo);
public:
	static void Init(int* argcp, char** argv);
	static void Display();
	static void RunMainLoop();
	static void Reshape(int width, int height);
	static void OnKeyboard(unsigned char key, int x, int y);
	static void OnSpecialKeys(int key, int x, int y);
};
