#pragma once

class BoardLayout
{
public:
	static const char AsciiWallHorizontal = '|';
	static const char AsciiWallVertical = '-';
	static const char AsciiWallEdgeUpperLeft = '^';
	static const char AsciiWallEdgeUpperRight = '>';
	static const char AsciiWallEdgeLowerRight = 'v';
	static const char AsciiWallEdgeLowerLeft = '<';
	static const char AsciiEmpty = ' ';
	static const char AsciiBait = '.';
	static const char AsciiBaitSpecial = '#';
	static const char AsciiTunnelRightDoor = 'r';
	static const char AsciiTunnelLeftDoor = 'l';
	static const char AsciiGhostDoor = '~';
	static const int Width = 31;
	static const int Height = 33;
	static const char AsciiBoard[Height][Width];
};
