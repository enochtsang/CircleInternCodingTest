#pragma once

#include <vector>

#include "RoomInfo.h"
#include "Item.h"
#include "Location.h"

// LevelLayout is an (N x N) grid of rooms where each room is connected to every adjacent room via a door
// There is a single exit door located along the boundary of the matrix (dungeon).
// ie. where the rows index == 0 or the column index == 0.
// There is one key to the exit door spawned at the bottom right room.
// To read more about types of walls read WallType.h

class LevelLayout
{
public:
	LevelLayout();

	Location spawnLocation() const;
	RoomInfo roomInfo(const Location & location) const;
	Item itemInRoom(const Location & location) const;

	Item takeItemFromRoom(const Location & location);

private:
	Location mExitRoom  = {0, 0};
	Direction mExitDirection = Direction::North;
	std::vector<std::pair<Item, Location>> mItemsAndLocations;
};

