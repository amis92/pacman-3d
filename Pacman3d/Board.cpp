#include "Board.h"
#include "ErrorCodes.h"

Board::Board()
	: Cells()
{
	for (auto i = 0; i < YLength; ++i)
	{
		for (auto j = 0; j < XLength; ++j)
		{
			Cells[i][j] = BoardLayout::AsciiBoard[i][j];
		}
	}
}

const BoardCell& Board::GetCell(int x, int y) const
{
	if (x < 0 || x >= XLength ||
		y < 0 || y >= YLength)
	{
		throw PacmanException(OutOfBoundsError);
	}
	return Cells[y][x];
}
