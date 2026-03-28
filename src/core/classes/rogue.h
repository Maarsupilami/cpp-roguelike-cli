#pragma once
#include "player.h"
#include "game_constants.h"
#include <cstdlib>

class Rogue : public Player {
    public:
        Rogue(std::string name)
            :   Player(
                    name,
                    ROGUE_HP,
                    ROGUE_ATTACK,
                    ROGUE_DEFENSE,
                    ROGUE_CRIT) {}
        
        int calculateDamage(const Character& target) const override {
            int baseDamage = attackPower - (target.getDefense() / 2) + (rand() % 7 - 3);
            float roll = (float)rand() / RAND_MAX;
            if (roll < critChance) return baseDamage * 2;
            return baseDamage;

        }
};