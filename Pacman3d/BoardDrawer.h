#pragma once
#include "Board.h"

// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include <GL/gl.h>
#include "Game.h"

class BoardDrawer
{
	const Board& board;
	GLuint textures[Game::TexturesSize];

	void DrawFloorTexture(const int floorTextureIndex) const;
	void DrawBait() const;
	void DrawSpecialBait() const;
	void DrawFloor(const BoardCell& boardCell) const;
	void DrawWall(const BoardCell& boardCell) const;
	void DrawBoardCell(const BoardCell& boardCell) const;
	void DrawScore() const;
	void DrawBoard() const;
	void DrawWallStraightSeg(bool vertical) const;
	void DrawWallEdgeSeg(const WallEdgeType wallEdgeType) const;
	void DrawPacman() const;
public:
	explicit BoardDrawer(const Board& board, GLuint textures[Game::TexturesSize]);
	void Draw(int frameNo) const;
};
