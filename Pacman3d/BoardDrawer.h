#pragma once
#include "Board.h"

class BoardDrawer
{
	const Board& board;

	void DrawBoard() const;
	void DrawWallStraightSeg(bool vertical) const;
	void DrawWallEdgeSeg(int x, int y) const;
	void DrawPacman() const;
public:
	explicit BoardDrawer(const Board& board);
	void Draw() const;
};
