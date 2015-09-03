#include "Board.h"
#include "ErrorCodes.h"

Board::Board()
	: Cells()
{
	xPacmanOffset = 14.5;
	yPacmanOffset = -24;
	xPacmanDirection = -1;
	yPacmanDirection = 0;
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

double Board::GetXPacmanOffset() const
{
	return xPacmanOffset;
}

double Board::GetYPacmanOffset() const
{
	return yPacmanOffset;
}

double Board::GetXPacmanDirection() const
{
	return xPacmanDirection;
}

double Board::GetYPacmanDirection() const
{
	return yPacmanDirection;
}