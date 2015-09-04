#pragma once
#include "BoardCell.h"
#include "BoardLayout.h"

class Board
{
public:
	static const int XLength = BoardLayout::Width - 1 /*for string-closing \0*/;
	static const int YLength = BoardLayout::Height;
private:
	static const int upScaleFactor = 100;
	static const int moveOffset = 10;
	static const int baitPoints = 10;
	static const int specialBaitPoints = 50;
	static const int newDirectionTimeoutSteps = 10;
	BoardCell Cells[YLength][XLength];
	int xPacmanOffset, yPacmanOffset;
	int xPacmanDirection, yPacmanDirection;
	int xPacmanFutureDirection, yPacmanFutureDirection;
	long score;
	int newDirectionSteps;

	const BoardCell& GetNextCell(int moveOffset, int xOffset, int yOffset, int xDirection, int yDirection) const;
public:
	explicit Board(int initialScore = 0);
	const BoardCell& GetCell(int x, int y) const;
	double GetXPacmanOffset() const;
	double GetYPacmanOffset() const;
	double GetXPacmanDirection() const;
	double GetYPacmanDirection() const;

	// Sets direction for pacman. only 1,0,-1 values are allowed, and at least
	// one of x,y must be zero.
	void SetPacmanDirection(int x, int y);
	void HandlePacmanOnNewField();
	void MovePacman();
	long GetScore() const;
	bool IsGameEnd() const;
};
