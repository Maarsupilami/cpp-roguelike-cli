#pragma once
#include "enemy.h"
#include "game_constants.h"

class GoblinChief : public Enemy{
    public:
        GoblinChief(std::string name)
            :   Enemy(
                    name,
                    GOBLIN_CHIEF_HP,
                    GOBLIN_CHIEF_ATTACK,
                    GOBLIN_CHIEF_DEFENSE,
                    GOBLIN_CHIEF_EXP_REWARD,
                    GOBLIN_CHIEF_GOLD_REWARD
                ) {}
};