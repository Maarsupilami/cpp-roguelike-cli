#pragma once
#include "enemy.h"
#include "game_constants.h"

class Goblin : public Enemy {
    public:
        Goblin(std::string name)
            :   Enemy(
                    name,
                    GOBLIN_STATS.hp,
                    GOBLIN_STATS.attack,
                    GOBLIN_STATS.defense,
                    GOBLIN_STATS.expReward,
                    GOBLIN_STATS.goldReward
                ) {}
};