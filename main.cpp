// CircleInternCodingTest2021.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string.h>
#include <chrono>
#include <thread>

#include "Direction.h"
#include "WallType.h"
#include "LevelLayout.h"
#include "RoomInfo.h"

/* INSTRUCTIONS

    This is a game where the player is trapped in a dungeon and must navigate their way out.
    There is one exit door and one key, the player must find the key and use it to exit.
    Read more about the shape of the dungeon at LevelLayout.h

    For this test, there is one required refactoring task outlined below the recommendations section.
    After, add as many features to this game as you can within the time alloted.
    But go for quality over quantity.
    Well-written bug-free implementations are better than many low quality implementations.
    Please also use git to provide a diff of the changes before and after.
    The diff can be in any format, for example a diff in a git GUI like fork.
*/

/* RECOMMENDATIONS

    - Follow the coding conventions that are already in the code
    - Do a mix of easy, medium, and hard features, starting with the easy ones.
    - Edit the code as if someone else needs to continue to add features after, i.e. flexible and easy to read
*/

/* REQUIRED REFACTORING TASK

    The only required change is to refactor the variables `playerItem` and `playerPosition` from `main()`
    into a new class called `Player`. Ensure to provide useful and expressive member functions for
    mutating the new `Player` class.
*/

/* POTENTIAL FEATURES TO ADD

    [EASY]
        [-] Show a graphical representation of the current room
        [-] Tell the player how many moves they used at the end of the game
        [-] Randomize map size
        [-] Randomize player spawn location
        [-] Randomize key spawn location
    [MEDIUM]
        [-] Randomly set some doors to walls
        [-] Require multiple keys to open the door
        [-] Add an option for the player to view their inventory
        [-] Add the option at the end to play again or to exit
        [-] Handle invalid input gracefully
    [HARD]
        [-] Write some tests for LevelLayout (framework not required)
        [-] Allow the player to view a map of already explored areas
        [-] Create a hunger system where the player must look for food to keep exploring
        [-] Add hazards to rooms that deteriorate the player's health
        [-] Change map generation to not just be a 2D square

    Feel free to be creative and add any features you think would be cool!
    This list is a recommendation not a checklist.
    We just want to see the extent of your coding skills, how you show us is up to you!
*/

/* WHAT WE'RE LOOKING FOR

    - Code changes that are easy to understand
    - Code changes that follow the existing design flow and coding conventions
    - Evidence of being able to handle complexity

    We are not looking for as many ticks as possible in the feature list!
*/

namespace
{
    Direction handleInput()
    {
        std::string input;
        std::cout << "Where would you like to go? [w/d/s/a]: ";
        std::cin >> input;

        if (input == "w")
        {
            return Direction::North;
        }
        else if (input == "a")
        {
            return Direction::West;
        }
        else if (input == "s")
        {
            return Direction::South;
        }
        else if (input == "d")
        {
            return Direction::East;
        }

        return Direction::North;
    }

    void inspectRoom(RoomInfo roomInfo)
    {
        for (const auto & directionAndWallType : roomInfo.wallTypes)
        {
            std::cout
                << "    To the "
                << directionToStr(directionAndWallType.first)
                << ":\t"
                << wallTypeToStr(directionAndWallType.second) << std::endl;
        }
    }
}

int main()
{
    LevelLayout levelLayout;
    auto playerItem = Item::NoItem;
    auto playerPosition = levelLayout.spawnLocation();
    auto playerExited = false;
    RoomInfo currentRoom = levelLayout.roomInfo(playerPosition);

    std::cout << "You find yourself in a cold musky room, you know you must escape..." << std::endl;


    while (!playerExited)
    {
        std::cout << std::endl << "================================" << std::endl;
        inspectRoom(currentRoom);
        std::cout << "================================" << std::endl;

        auto direction = handleInput();
        if (currentRoom.wallTypes[direction] == WallType::Wall)
        {
            std::cout << "\tYou ran into a wall, doi..." << std::endl;
        }
        else if (currentRoom.wallTypes[direction] == WallType::Door)
        {
            switch (direction)
            {
                case Direction::North:
                    playerPosition.y -= 1;
                    break;
                case Direction::East:
                    playerPosition.x += 1;
                    break;
                case Direction::South:
                    playerPosition.y += 1;
                    break;
                case Direction::West:
                    playerPosition.x -= 1;
                    break;
            }
            std::cout << "\tYou head " << directionToStr(direction) << "..." << std::endl;
            currentRoom = levelLayout.roomInfo(playerPosition);

            if (currentRoom.item != Item::NoItem)
            {
                std::cout << "\tYou found something!" << std::endl;
                std::cout << "\tOBTAINED: " << itemToStr(currentRoom.item) << std::endl;
                playerItem = levelLayout.takeItemFromRoom(playerPosition);
            }
        }
        else if (currentRoom.wallTypes[direction] == WallType::ExitDoor)
        {
            if (playerItem == Item::ExitKey)
            {
                std::cout << "\tYou unlock the door and walk up the stairs..." << std::endl;
                playerExited = true;
            }
            else
            {
                std::cout << "\tThe door is locked, you must find the key..." << std::endl;
            }
        }

        // Pause to give the player time to read what happened
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout
        << "\tAnd you are finally free!" << std::endl
        << std::endl
        << "<GAME OVER>" << std::endl
        << "PRESS ENTER TO EXIT...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
