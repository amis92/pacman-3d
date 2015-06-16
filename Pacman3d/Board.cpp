#include "Board.h"
#include "ErrorCodes.h"

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
}

const BoardCell& Board::GetCell(int x, int y) const
{
	if (x < 0 || x >= BoardLayout::Width ||
		y < 0 || y >= BoardLayout::Height)
	{
		throw PacmanException(OutOfBoundsError);
	}
	return Cells[y][x];
}
