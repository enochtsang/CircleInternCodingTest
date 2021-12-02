#pragma once

#include <string>

// Every wall is a WallType

enum class WallType
{
    Wall, // Impassable terrain
    Door, // An entrance to another room
    ExitDoor, // Requires a key, but passing through this beats the game
};

inline std::string wallTypeToStr(WallType wallType)
{
    switch (wallType)
    {
        case WallType::Wall:
            return "Wall |||";
        case WallType::Door:
            return "Door [ ]";
        case WallType::ExitDoor:
            return "Exit door [x]";
    }

    return "[ERROR]";
}
