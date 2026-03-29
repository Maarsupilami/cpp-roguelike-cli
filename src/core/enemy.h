#pragma once
#include "character.h"

enum class EnemyType {
    GOBLIN,
    SKELETON,
    TROLL,
    COUNT
};

class Enemy : public Character {
    private:
        int experienceReward;
        int goldReward;
    public:
        Enemy(std::string name, int hp, int attackPower, int defense, int expReward, unsigned int goldReward)
            :   Character(name, hp, attackPower, defense),
                experienceReward(expReward),
                goldReward(goldReward) {}

        int getExpReward()  const { return experienceReward; }
        unsigned int getGoldReward() const { return goldReward; }
};