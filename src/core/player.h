#pragma once
#include "character.h"
#include <vector>
#include <string>
#include "item.h"

class Player : public Character {
    protected:
        int experience;
        int gold;
        float critChance;
        std::vector<Item> inventory;

    public:
        Player(std::string name, int hp, int attackPower, int defense, float critChance)
            :   Character(name, hp, attackPower, defense),
                experience(0),
                gold(0),
                critChance(critChance) {}
        
        void addItem(const Item& item){
            inventory.push_back(item);
        }

        const std::vector<Item>& getInventory() const { return inventory; }
};