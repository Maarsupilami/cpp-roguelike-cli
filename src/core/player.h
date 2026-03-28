#pragma once
#include "character.h"
#include <vector>
#include <string>

class Player : public Character {
    private:
        int experience;
        int gold;
        float critChance;
    public:
        Player(std::string name, int hp, int attackPower, int defense, float critChance)
            :   Character(name, hp, attackPower, defense),
                experience(0),
                gold(0),
                critChance(critChance) {}
};