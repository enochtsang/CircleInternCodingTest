#pragma once

#include <string.h>

enum class Direction
{
    North,
    East,
    South,
    West
};

inline std::string directionToStr(Direction direction)
{
    switch (direction)
    {
        case Direction::North:
            return "north";
        case Direction::East:
            return "east";
        case Direction::South:
            return "south";
        case Direction::West:
            return "west";
    }

    return "[ERROR]";
}

