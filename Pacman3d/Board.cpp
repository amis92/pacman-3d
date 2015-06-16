#include "Board.h"

Board::Board()
	: Cells()
{
	for (auto i = 0; i < BoardLayout::Height; ++i)
	{
		for (auto j = 0; j < BoardLayout::Width; ++j)
		{
			Cells[i][j] = BoardLayout::AsciiBoard[i][j];
		}
	}
	const auto& x = GetCell(0, 0);
}

const BoardCell& Board::GetCell(int x, int y) const
{
	return Cells[y][x];
}