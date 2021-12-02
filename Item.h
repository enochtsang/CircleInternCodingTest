#pragma once

#include <string>

enum class Item
{
    NoItem,
    ExitKey,
};

inline std::string itemToStr(Item item)
{
    switch (item)
    {
        case Item::NoItem:
            return "No Item";
        case Item::ExitKey:
            return "Exit Key";
    }

    return "[ERROR]";
}