#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>

class CubeVerticesDrawer
{
public:
	static void DrawFrontVertices(bool setNormals);
	static void DrawRearVertices(bool setNormals);
	static void DrawLeftVertices(bool setNormals);
	static void DrawRightVertices(bool setNormals);
	static void DrawTopVertices(bool setNormals);
	static void DrawBottomVertices(bool setNormals);
};
