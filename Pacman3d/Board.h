#pragma once
#include "BoardCell.h"
#include "BoardLayout.h"

class Board
{
public:
	static const int XLength = BoardLayout::Width - 1 /*for string-closing \0*/;
	static const int YLength = BoardLayout::Height;
private:
	BoardCell Cells[YLength][XLength];

public:
	Board();
	const BoardCell& GetCell(int x, int y) const;
};
