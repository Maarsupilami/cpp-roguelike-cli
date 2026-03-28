#pragma once
#include <string>

enum class ItemType {
    POTION,
    WEAPON,
    ARMOR,
    SCROLL
};

class Item{
    protected:
        std::string name;
        ItemType itemType;
    
    public:
        Item(std::string name, ItemType itemType)
            :   name(name), itemType(itemType) {}
};