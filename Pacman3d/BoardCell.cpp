#include "BoardCell.h"
#include "BoardLayout.h"

ItemType BoardCell::GetItemType(const char c)
{
	switch (c)
	{
	case BoardLayout::AsciiBait:
	case BoardLayout::AsciiBaitSpecial:
	case BoardLayout::AsciiEmpty:
		return Floor;
	case BoardLayout::AsciiTunnelLeftDoor:
	case BoardLayout::AsciiTunnelRightDoor:
		return Tunnel;
	case BoardLayout::AsciiGhostDoor:
		return GhostDoor;
	default:
		return Wall;
	}
}

WallType BoardCell::GetWallType(const char c)
{
	switch (c)
	{
	case BoardLayout::AsciiWallHorizontal:
		return Horizontal;
	case BoardLayout::AsciiWallVertical:
		return Vertical;
	default:
		return Edge;
	}
}

WallEdgeType BoardCell::GetWallEdgeType(const char c)
{
	switch (c)
	{
	case BoardLayout::AsciiWallEdgeLowerLeft:
		return LowerLeft;
	case BoardLayout::AsciiWallEdgeLowerRight:
		return LowerRight;
	case BoardLayout::AsciiWallEdgeUpperLeft:
		return UpperLeft;
	case BoardLayout::AsciiWallEdgeUpperRight:
		return UpperRight;
	default:
		return UpperLeft;
	}
}

FloorContentType BoardCell::GetContentType(const char c)
{
	switch (c)
	{
	case BoardLayout::AsciiBait:
		return Bait;
	case BoardLayout::AsciiBaitSpecial:
		return SpecialBait;
	default:
		return Empty;
	}
}

BoardCell::BoardCell(char c) :
	itemType(GetItemType(c)),
	wallType(GetWallType(c)),
	wallEdgeType(GetWallEdgeType(c)),
	floorContentType(GetContentType(c))
{
}

BoardCell::BoardCell(
	const ItemType itemType,
	const FloorContentType floorContentType,
	const WallType wallType,
	const WallEdgeType wallEdgeType) :
	itemType(itemType), wallType(wallType), wallEdgeType(wallEdgeType),
	floorContentType(floorContentType)
{
}

ItemType BoardCell::GetType() const
{
	return itemType;
}

WallType BoardCell::GetWallType() const
{
	return wallType;
}

WallEdgeType BoardCell::GetWallEdgeType() const
{
	return wallEdgeType;
}

FloorContentType BoardCell::GetFloorContentType() const
{
	return floorContentType;
}

void BoardCell::SetFloorContentType(FloorContentType newType)
{
	floorContentType = newType;
}