#pragma once
#include "enemy.h"
#include "game_constants.h"

class Troll : public Enemy {
    public:
        Troll(std::string name)
            :   Enemy(
                    name,
                    TROLL_HP,
                    TROLL_ATTACK,
                    TROLL_DEFENSE,
                    TROLL_EXP_REWARD,
                    TROLL_GOLD_REWARD
                ) {}
};