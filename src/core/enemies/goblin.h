#pragma once
#include "enemy.h"
#include "game_constants.h"

class Goblin : public Enemy {
    public:
        Goblin(std::string name)
            :   Enemy(
                    name,
                    GOBLIN_HP,
                    GOBLIN_ATTACK,
                    GOBLIN_DEFENSE,
                    GOBLIN_EXP_REWARD,
                    GOBLIN_GOLD_REWARD
                ) {}
};