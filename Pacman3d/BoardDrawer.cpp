#include "BoardDrawer.h"

#include <Windows.h>
#include <GL/GL.h>
#include "glut.h"

static const auto BoardWidth = BoardLayout::Width;
static const auto BoardHeight = BoardLayout::Height;
static const GLfloat NormalsTop[]    = {  0.f,  1.f,  0.f };
static const GLfloat NormalsBottom[] = {  0.f, -1.f,  0.f };
static const GLfloat NormalsLeft[]   = { -1.f,  0.f,  0.f };
static const GLfloat NormalsRight[]  = { -1.f,  0.f,  0.f };
static const GLfloat NormalsFront[]  = {  0.f,  0.f,  1.f };
static const GLfloat NormalsBack[]   = {  0.f,  0.f, -1.f };

BoardDrawer::BoardDrawer(const Board& board)
	: board(board)
{
}

void BoardDrawer::Draw() const
{
	DrawBoard();
}

void BoardDrawer::DrawBoard() const
{
	glPushMatrix();
	//glTranslatef(float(BoardWidth) / 2.0f, float(BoardHeight) / 2.0f, 0.0f);
	DrawWallStraightSeg(true);
	glPopMatrix();
}

void BoardDrawer::DrawWallStraightSeg(bool vertical) const
{
	//glColor3f(1.f, 0.f, 0.f);
	//glBegin(GL_QUADS);

	//const auto halfSize = 0.5f;

	//glNormal3fv(NormalsFront);
	//glVertex3f(-halfSize, -halfSize, halfSize);
	//glVertex3f( halfSize, -halfSize, halfSize);
	//glVertex3f( halfSize,  halfSize, halfSize);
	//glVertex3f(-halfSize,  halfSize, halfSize);

	//glEnd();
	GLfloat diffuse[] = {0.7, 0.7, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glutSolidSphere(3.0, 24, 10);
}

void BoardDrawer::DrawWallEdgeSeg(int x, int y) const
{
}

void BoardDrawer::DrawPacman() const
{
}
