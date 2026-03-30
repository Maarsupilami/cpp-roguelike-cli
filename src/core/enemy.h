#pragma once
#include "character.h"
#include <cstdlib>
#include <memory>
#include "item.h"
#include "items/potion.h"

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
        float dropChance = 0.3f;

    public:
        Enemy(std::string name, int hp, int attackPower, int defense, int expReward, unsigned int goldReward)
            :   Character(name, hp, attackPower, defense),
                experienceReward(expReward),
                goldReward(goldReward) {}

        int getExpReward()  const { return experienceReward; }
        unsigned int getGoldReward() const { return goldReward; }

        virtual std::unique_ptr<Item> drop() {
            float roll = (float)rand() / RAND_MAX;
            if (roll < dropChance) return std::make_unique<HealthPotion>();
            return nullptr;
        };
};