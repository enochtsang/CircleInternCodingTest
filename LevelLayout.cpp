#include <algorithm>
#include <cstdlib>

#include <ctime>

#include "LevelLayout.h"

namespace
{
	const auto cMapSize = 4;
}

LevelLayout::LevelLayout()
{
	// Initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// set key location
	auto keyAndLocation = std::make_pair<Item, Location>(
		Item::ExitKey,
		{cMapSize - 1, cMapSize - 1});
	mItemsAndLocations.push_back(keyAndLocation);

	// determine exit room
	mExitDirection = static_cast<Direction>(rand() % 4);
	switch (mExitDirection)
	{
		case Direction::North:
			mExitRoom = { rand() % cMapSize, 0 };
			break;
		case Direction::East:
			mExitRoom = { cMapSize - 1, rand() % cMapSize };
			break;
		case Direction::South:
			mExitRoom = { rand() % cMapSize, cMapSize - 1 };
			break;
		case Direction::West:
			mExitRoom = { 0, rand() % cMapSize };
			break;
	}
}

Location LevelLayout::spawnLocation() const
{
	return {0, 0};
}

RoomInfo LevelLayout::roomInfo(const Location & location) const
{
	RoomInfo roomInfo;

	// Determine which directions are walls
	roomInfo.wallTypes[Direction::North]
		= (location.y == 0) ? WallType::Wall : WallType::Door;
	roomInfo.wallTypes[Direction::East]
		= (location.x == cMapSize - 1) ? WallType::Wall : WallType::Door;
	roomInfo.wallTypes[Direction::South]
		= (location.y == cMapSize - 1) ? WallType::Wall : WallType::Door;
	roomInfo.wallTypes[Direction::West]
		= (location.x == 0) ? WallType::Wall : WallType::Door;

	// Indicate the exit door if it is in this room
	if (location == mExitRoom)
	{
		roomInfo.wallTypes[mExitDirection] = WallType::ExitDoor;
	}

	// Indicate whether the room has any items
	roomInfo.item = itemInRoom(location);;

	return roomInfo;
}

Item LevelLayout::itemInRoom(const Location & location) const
{
	for (const auto & itemAndLocation : mItemsAndLocations)
	{
		if (itemAndLocation.second == location)
		{
			return itemAndLocation.first;
		}
	}

	return Item::NoItem;
}

Item LevelLayout::takeItemFromRoom(const Location & location)
{
	auto itemToTake = itemInRoom(location);
	if (itemToTake == Item::NoItem)
	{
		return Item::NoItem;
	}

	auto itemIndex = 0;
    for (const auto & itemAndLocation : mItemsAndLocations)
    {
        if (itemAndLocation.second == location)
        {
            break;
        }
		itemIndex++;
    }

	mItemsAndLocations.erase(mItemsAndLocations.begin() + itemIndex);

	return itemToTake;
}
