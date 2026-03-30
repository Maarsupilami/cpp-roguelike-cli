#pragma once
#include "enemy.h"
#include "game_constants.h"

class GoblinChief : public Enemy{
    public:
        GoblinChief(std::string name)
            :   Enemy(
                    name,
                    GOBLIN_CHIEF_STATS.hp,
                    GOBLIN_CHIEF_STATS.attack,
                    GOBLIN_CHIEF_STATS.defense,
                    GOBLIN_CHIEF_STATS.expReward,
                    GOBLIN_CHIEF_STATS.goldReward
                ) {}
};