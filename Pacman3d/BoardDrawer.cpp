#include "BoardDrawer.h"

#include <Windows.h>
#include <GL/GL.h>
#include "glut.h"
#include "Game.h"
#include "CubeVerticesDrawer.h"

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
static const GLfloat zAxis90degRotationMatrix[] = {
	/*1st column*/0., -1, 0., 0.,/*2nd column*/ 1., 0., 0., 0.,
	/*3rd column*/ 0., 0., 1., 0., /*4th column*/ 0., 0., 0., 1.};
static const GLfloat zAxis180degRotationMatrix[] = {
	/*1st column*/-1., 0., 0., 0.,/*2nd column*/ 0., -1., 0., 0.,
	/*3rd column*/ 0., 0., 1., 0., /*4th column*/ 0., 0., 0., 1.};
static const GLfloat zAxis270degRotationMatrix[] = {
	/*1st column*/0., 1, 0., 0.,/*2nd column*/ -1., 0., 0., 0.,
	/*3rd column*/ 0., 0., 1., 0., /*4th column*/ 0., 0., 0., 1.};
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

void BoardDrawer::DrawFloorTexture(const int floorTextureIndex) const
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[floorTextureIndex]);
	glBegin(GL_QUADS);

	//rear face
	glNormal3fv(NormalsFront);
	CubeVerticesDrawer::DrawRearVertices(false);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void BoardDrawer::DrawBait() const
{
	glPushMatrix();
	glutSolidSphere(.2, 24, 10);
	glPopMatrix();
}

void BoardDrawer::DrawSpecialBait() const
{
	glPushMatrix();
	glutSolidSphere(.35, 24, 10);
	glPopMatrix();
}

void BoardDrawer::DrawFloor(const BoardCell& boardCell) const
{
	DrawFloorTexture(Game::FloorTextureIndex);
	switch (boardCell.GetFloorContentType())
	{
	case Empty: break;
	case Bait:
		DrawBait();
		break;
	case SpecialBait:
		DrawSpecialBait();
		break;
	default: break;
	}
}

void BoardDrawer::DrawWall(const BoardCell& boardCell) const
{
	DrawFloorTexture(Game::WallFloorTextureIndex);
	switch (boardCell.GetWallType())
	{
	case Horizontal: DrawWallStraightSeg(false);
		break;
	case Vertical: DrawWallStraightSeg(true);
		break;
	case Edge: DrawWallEdgeSeg(boardCell.GetWallEdgeType());
		break;
	default: break;
	}
}

void BoardDrawer::DrawBoardCell(const BoardCell& boardCell) const
{
	glPushMatrix();
	switch (boardCell.GetType())
	{
	case Void: break;
	case GhostDoor: //TODO
	case Floor: DrawFloor(boardCell);
		break;
	case Wall: DrawWall(boardCell);
		break;
	case Tunnel: break;
	default: break;
	}
	glPopMatrix();
}

void BoardDrawer::DrawScore() const
{
	glPushMatrix();
	auto score = board.GetScore();
	auto chars = score == 0 ? 0 : 10;
	auto i = 1000000000;
	while (chars > 0 && score / i % 10 == 0)
	{
		i /= 10;
		chars--;
	}
	chars = chars == 0 ? 1 : chars;
	glTranslated(14.5 - double(chars)/2.0, -32.5, 1.0);
	glScaled(0.01, 0.01, 0.01);
	if (score == 0)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
		glTranslatef(0.5, 0.0, 0.0);
	}
	else
	{
		long x = 10000;
		while (score > 0 && score / x % 10 == 0)
		{
			x /= 10;
		}
		for (; x > 0; x /= 10)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, score / x % 10 + '0');
			glTranslatef(0.5, 0.0, 0.0);
		}
	}
	//glutStrokeCharacter(GLUT_STROKE_ROMAN, score / 1000 % 10 + '0');
	//glTranslatef(0.5, 0.0, 0.0);
	//glutStrokeCharacter(GLUT_STROKE_ROMAN, score / 100 % 10 + '0');
	//glTranslatef(0.5, 0.0, 0.0);
	//glutStrokeCharacter(GLUT_STROKE_ROMAN, score / 10 % 10 + '0');
	//glTranslatef(0.5, 0.0, 0.0);
	//glutStrokeCharacter(GLUT_STROKE_ROMAN, score % 10 + '0');
	glPopMatrix();
}

void BoardDrawer::DrawBoard() const
{
	glPushMatrix();

	GLfloat diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glTranslatef(-float(Board::XLength) / 2, float(Board::YLength) / 2 - 1, 0.f);
	for (auto x = 0; x < Board::XLength; x++)
	{
		glPushMatrix();
		glTranslatef(1.f * float(x), 0.f, 0.f);
		for (auto y = 0; y < Board::YLength; y++)
		{
			glPushMatrix();
			glTranslatef(0.f, -1.f * float(y), 0.f);
			DrawBoardCell(board.GetCell(x, y));
			glPopMatrix();
		}
		glPopMatrix();
	}
	DrawPacman();
	DrawScore();
	glPopMatrix();
}

void BoardDrawer::DrawWallStraightSeg(bool vertical) const
{
	glPushMatrix();
	glScalef(vertical ? 1.0 : 0.5, vertical ? 0.5 : 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[Game::WallTextureIndex]);
	glBegin(GL_QUADS);

	CubeVerticesDrawer::DrawFrontVertices(true);
	CubeVerticesDrawer::DrawRearVertices(true);
	CubeVerticesDrawer::DrawLeftVertices(true);
	CubeVerticesDrawer::DrawRightVertices(true);
	CubeVerticesDrawer::DrawTopVertices(true);
	CubeVerticesDrawer::DrawBottomVertices(true);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void BoardDrawer::DrawWallEdgeSeg(const WallEdgeType wallEdgeType) const
{
	//drawing an upper-left edge:
	/*
	    ______
	   /  ___/|
      /__/|  ||
	  | | |  ||
	  | | |__|/
	  |_|/

	*/

	glPushMatrix();
	switch (wallEdgeType)
	{
	case UpperLeft: break;
	case UpperRight: glMultMatrixf(zAxis90degRotationMatrix);
		break;
	case LowerRight: glMultMatrixf(zAxis180degRotationMatrix);
		break;
	case LowerLeft: glMultMatrixf(zAxis270degRotationMatrix);
		break;
	default: break;
	}
	glTranslatef(0.25, -0.25, 0.);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[Game::WallTextureIndex]);

	//top+left full walls
	glPushMatrix();
	{
		glTranslatef(-0.125, 0.125, 0.);
		glScalef(0.75, 0.75, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawTopVertices(true);
		CubeVerticesDrawer::DrawLeftVertices(true);
		glEnd();
	}
	glPopMatrix();
	//front+back
	glPushMatrix();
	{
		glTranslatef(0.125, 0.25, 0.);
		glScalef(0.25, 0.5, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawFrontVertices(true);
		CubeVerticesDrawer::DrawRearVertices(true);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.25, 0.25, 0.);
		glScalef(0.5, 0.5, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawFrontVertices(true);
		CubeVerticesDrawer::DrawRearVertices(true);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.25, -0.125, 0.);
		glScalef(0.5, 0.25, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawFrontVertices(true);
		CubeVerticesDrawer::DrawRearVertices(true);
		glEnd();
	}
	glPopMatrix();
	//bottom
	glPushMatrix();
	{
		glTranslatef(-0.25, 0.25, 0.);
		glScalef(0.5, 1., 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawBottomVertices(true);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.125, 0.5, 0.);
		glScalef(0.25, 1., 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawBottomVertices(true);
		glEnd();
	}
	glPopMatrix();
	//right
	glPushMatrix();
	{
		glTranslatef(-0.25, 0.25, 0.);
		glScalef(1., 0.5, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawRightVertices(true);
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.5, -0.125, 0.);
		glScalef(1., 0.25, 1.);
		glBegin(GL_QUADS);
		CubeVerticesDrawer::DrawRightVertices(true);
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void BoardDrawer::DrawPacman() const
{
	glPushMatrix();
	glTranslatef(board.GetXPacmanOffset(), -board.GetYPacmanOffset(), 0);
	GLfloat diffuse[] = {0.7f, 0.7f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glutSolidSphere(.5, 24, 10);
	glPopMatrix();
}
