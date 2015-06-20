#include "BoardDrawer.h"

#include <Windows.h>
#include <GL/GL.h>
#include "glut.h"
#include "Game.h"

static const auto BoardWidth = BoardLayout::Width;
static const auto BoardHeight = BoardLayout::Height;
static const GLfloat NormalsTop[] = {0.f, 1.f, 0.f};
static const GLfloat NormalsBottom[] = {0.f, -1.f, 0.f};
static const GLfloat NormalsLeft[] = {-1.f, 0.f, 0.f};
static const GLfloat NormalsRight[] = {1.f, 0.f, 0.f};
static const GLfloat NormalsFront[] = {0.f, 0.f, 1.f};
static const GLfloat NormalsRear[] = {0.f, 0.f, -1.f};

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

static const float VertBL[] = { 0.0f, 0.0f };
static const float VertBR[] = { 1.0f, 0.0f };
static const float VertTR[] = { 1.0f, 1.0f };
static const float VertTL[] = { 0.0f, 1.0f };

BoardDrawer::BoardDrawer(const Board& board, GLuint textures[Game::TexturesSize])
	: board(board)
{
	for (auto i = 0; i < Game::TexturesSize; ++i)
	{
		this->textures[i] = textures[i];
	}
}

void BoardDrawer::Draw(int frameNo) const
{
	DrawBoard();
}

void BoardDrawer::DrawBoard() const
{
	//glTranslatef(float(BoardWidth) / 2.0f, float(BoardHeight) / 2.0f, 0.0f);
	DrawWallStraightSeg(true);
	DrawPacman();
}

void BoardDrawer::DrawWallStraightSeg(bool vertical) const
{
	glPushMatrix();
	glTranslatef(0.f, 5.f, 5.f);
	glRotatef(-20, 1.f, 0.f, 0.f);
	auto scale = 5.;
	glScaled(scale, scale, scale);


	//GLfloat diffuse[] = { 0.5, 0.5, 1., 1.0 };
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);

	//front face
	glNormal3fv(NormalsFront);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFTL);

	//rear face
	glNormal3fv(NormalsRear);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTL);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTR);

	//top face
	glNormal3fv(NormalsTop);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFTL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFTR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTL);

	//bottom face
	glNormal3fv(NormalsBottom);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFBL);

	//left face
	glNormal3fv(NormalsLeft);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertRBL);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertFBL);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertFTL);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertRTL);

	//right face
	glNormal3fv(NormalsRight);
	glTexCoord2fv(VertBL);
	glVertex3fv(VertFBR);
	glTexCoord2fv(VertBR);
	glVertex3fv(VertRBR);
	glTexCoord2fv(VertTR);
	glVertex3fv(VertRTR);
	glTexCoord2fv(VertTL);
	glVertex3fv(VertFTR);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void BoardDrawer::DrawWallEdgeSeg(int x, int y) const
{
}

void BoardDrawer::DrawPacman() const
{
	glPushMatrix();
	GLfloat diffuse[] = {0.7, 0.7, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glutSolidSphere(3.0, 24, 10);
	glPopMatrix();
}
