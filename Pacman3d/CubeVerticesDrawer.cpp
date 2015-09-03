#include "CubeVerticesDrawer.h"

// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include <GL/GL.h>

// let's get cube veritces numbered:
/*
8*-----*7
/|    /|
1*-*5-2* *6
|/    |/
4*----3*

mnemonics (F-front/R-rear;T-top/B-bottom;L-left/R-right;):
1: FTL
2: FTR
3: FBR
4: FBL
5: RBL
6: RBR
7: RTR
8: RTL
*/

static const float VertFTL[] = {-0.5, 0.5, 0.5};
static const float VertFTR[] = {0.5, 0.5, 0.5};
static const float VertFBR[] = {0.5, -0.5, 0.5};
static const float VertFBL[] = {-0.5, -0.5, 0.5};

static const float VertRTL[] = {-0.5, 0.5, -0.5};
static const float VertRTR[] = {0.5, 0.5, -0.5};
static const float VertRBR[] = {0.5, -0.5, -0.5};
static const float VertRBL[] = {-0.5, -0.5, -0.5};

static const float VertBL[] = {0.0f, 0.0f};
static const float VertBR[] = {1.0f, 0.0f};
static const float VertTR[] = {1.0f, 1.0f};
static const float VertTL[] = {0.0f, 1.0f};
static const GLfloat NormalsTop[] = {0.f, 1.f, 0.f};
static const GLfloat NormalsBottom[] = {0.f, -1.f, 0.f};
static const GLfloat NormalsLeft[] = {-1.f, 0.f, 0.f};
static const GLfloat NormalsRight[] = {1.f, 0.f, 0.f};
static const GLfloat NormalsFront[] = {0.f, 0.f, 1.f};
static const GLfloat NormalsRear[] = {0.f, 0.f, -1.f};

void CubeVerticesDrawer::DrawFrontVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsFront);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFTL);
}

void CubeVerticesDrawer::DrawRearVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsRear);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTL);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTR);
}

void CubeVerticesDrawer::DrawLeftVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsLeft);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFBL);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFTL);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTL);
}

void CubeVerticesDrawer::DrawRightVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsRight);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFTR);
}

void CubeVerticesDrawer::DrawTopVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsTop);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFTL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFTR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTL);
}

void CubeVerticesDrawer::DrawBottomVertices(bool setNormals)
{
	if (setNormals) glNormal3fv(NormalsBottom);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFBL);
}
