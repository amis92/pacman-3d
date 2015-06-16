#pragma once
#include "Board.h"

class BoardDrawer
{
	const Board board;
public:
	explicit BoardDrawer(const Board& board);
	void DrawBoard() const;
	void DrawWallStraightSeg(const int x, const int y) const;
	void DrawWallEdgeSeg(const int x, const int y) const;
	void DrawPacman() const;
};
