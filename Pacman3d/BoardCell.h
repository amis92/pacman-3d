#pragma once

enum ItemType
{
	Void,
	Floor,
	Wall,
	Tunnel,
	GhostDoor
};

enum WallType
{
	Horizontal,
	Vertical,
	Edge
};

enum WallEdgeType
{
	UpperLeft,
	UpperRight,
	LowerLeft,
	LowerRight
};

enum FloorContentType
{
	Empty,
	Bait,
	SpecialBait
};

class BoardCell
{
	ItemType itemType;
	WallType wallType;
	WallEdgeType wallEdgeType;
	FloorContentType floorContentType;

	static ItemType GetItemType(const char c);
	static WallType GetWallType(const char c);
	static WallEdgeType GetWallEdgeType(const char c);
	static FloorContentType GetContentType(const char c);
public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	BoardCell(char c);
	explicit BoardCell(
		const ItemType itemType = Floor,
		const FloorContentType floorContentType = Empty,
		const WallType wallType = Horizontal,
		const WallEdgeType wallEdgeType = UpperLeft);

	ItemType GetType() const;
	WallType GetWallType() const;
	WallEdgeType GetWallEdgeType() const;
	FloorContentType GetFloorContentType() const;
	void SetFloorContentType(FloorContentType newType);
};
