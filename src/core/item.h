#pragma once
#include <string>

class Player;
class Enemy;

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

        virtual void use(Player& player, Enemy* enemy = nullptr) = 0;
        virtual ~Item() = default;
};