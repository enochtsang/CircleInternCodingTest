#pragma once

#include <map>

#include "WallType.h"
#include "Direction.h"
#include "Item.h"

struct RoomInfo
{
	std::map<Direction, WallType> wallTypes = {
		{ Direction::North, WallType::Wall },
		{ Direction::East, WallType::Wall },
		{ Direction::South, WallType::Wall },
		{ Direction::West, WallType::Wall },
	};

	Item item = Item::NoItem;
};
