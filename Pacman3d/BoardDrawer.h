#pragma once
#include "Board.h"

#include <Windows.h>
#include <GL/gl.h>
#include "Game.h"

class BoardDrawer
{
	const Board& board;
	GLuint textures[Game::TexturesSize];

	void DrawBoard() const;
	void DrawWallStraightSeg(bool vertical) const;
	void DrawWallEdgeSeg(int x, int y) const;
	void DrawPacman() const;
public:
	explicit BoardDrawer(const Board& board, GLuint textures[Game::TexturesSize]);
	void Draw(int frameNo) const;
};
