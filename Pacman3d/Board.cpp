#include "Board.h"
#include "ErrorCodes.h"
#include <cmath>

const BoardCell& Board::GetNextCell(int moveOffset, int xOffset, int yOffset, int xDirection, int yDirection) const
{
	auto xOnPoint = xOffset % upScaleFactor == 0;
	auto yOnPoint = yOffset % upScaleFactor == 0;
	if (xOnPoint && yOnPoint)
	{
		return Cells[yOffset / upScaleFactor + yDirection][xOffset / upScaleFactor + xDirection];
	}
	auto xNext = (xOffset + moveOffset * xDirection);
	auto yNext = (yOffset + moveOffset * yDirection);
	auto xNextOnPoint = xNext % upScaleFactor == 0;
	auto yNextOnPoint = yNext % upScaleFactor == 0;
	if (xNextOnPoint && yNextOnPoint)
	{
		return Cells[yNext / upScaleFactor][xNext / upScaleFactor];
	}
	return Cells[yOffset / upScaleFactor + (yDirection > 0 ? 1 : 0)]
		[xOffset / upScaleFactor + (xDirection > 0 ? 1 : 0)];
}

Board::Board()
	: Cells()
{
	xPacmanOffset = 1450;
	yPacmanOffset = 2400;
	xPacmanDirection = xPacmanFutureDirection = -1;
	yPacmanDirection = yPacmanFutureDirection = 0;
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
	return double(xPacmanOffset) / upScaleFactor;
}

double Board::GetYPacmanOffset() const
{
	return double(yPacmanOffset) / upScaleFactor;
}

double Board::GetXPacmanDirection() const
{
	return xPacmanDirection;
}

double Board::GetYPacmanDirection() const
{
	return yPacmanDirection;
}

void Board::SetPacmanDirection(int x, int y)
{
	if (x != 0 && y != 0)
	{
		throw PacmanException(PacmanDirectionError);
	}
	if (x < -1 || x > 1 || y < -1 || y > 1)
	{
		throw PacmanException(OutOfBoundsError);
	}
	xPacmanFutureDirection = x;
	yPacmanFutureDirection = y;
}

void Board::MovePacman()
{
	auto xOnPoint = xPacmanOffset % upScaleFactor == 0;
	auto yOnPoint = yPacmanOffset % upScaleFactor == 0;
	auto isChangingLeftRight = xPacmanDirection != 0 && xPacmanDirection + xPacmanFutureDirection == 0;
	auto isChangingUpDown = yPacmanDirection != 0 && yPacmanDirection + yPacmanFutureDirection == 0;
	if ((!xOnPoint && isChangingLeftRight) ^ (!yOnPoint && isChangingUpDown))
	{
		xPacmanDirection = xPacmanFutureDirection;
		yPacmanDirection = yPacmanFutureDirection;
	}
	else if (xOnPoint && yOnPoint && (xPacmanDirection != xPacmanFutureDirection || yPacmanDirection != yPacmanFutureDirection))
	{
		auto& nextFutureCell = GetNextCell(moveOffset, xPacmanOffset, yPacmanOffset, xPacmanFutureDirection, yPacmanFutureDirection);
		auto futureCellType = nextFutureCell.GetType();
		if (futureCellType == Floor || futureCellType == Tunnel)
		{
			xPacmanDirection = xPacmanFutureDirection;
			yPacmanDirection = yPacmanFutureDirection;
		}
	}
	auto& nextCell
		= GetNextCell(moveOffset, xPacmanOffset, yPacmanOffset, xPacmanDirection, yPacmanDirection);
	switch (nextCell.GetType())
	{
	case Tunnel:
	case Floor:
		xPacmanOffset += moveOffset * xPacmanDirection;
		yPacmanOffset += moveOffset * yPacmanDirection;
		break;
	case Void: break;
	case Wall: break;
	case GhostDoor: break;
	default: break;
	}
}
