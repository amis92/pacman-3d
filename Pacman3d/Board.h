#pragma once
#include "BoardCell.h"
#include "BoardLayout.h"

class Board
{
	BoardCell Cells[BoardLayout::Height][BoardLayout::Width];

public:
	Board();
	const BoardCell& GetCell(int x, int y) const;
};
