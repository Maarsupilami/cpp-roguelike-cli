#pragma once
#include "character.h"

class Enemy : public Character {
    private:
        int experienceReward;
        int goldReward;
    public:
        Enemy(std::string name, int hp, int attackPower, int defense, int expReward, int goldReward)
            : Character(name, hp, attackPower, defense) {}

        int getExpReward()  const { return experienceReward; }
        int getGoldReward() const { return goldReward; }
};