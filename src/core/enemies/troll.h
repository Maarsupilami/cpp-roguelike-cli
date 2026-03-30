#pragma once
#include "enemy.h"
#include "game_constants.h"

class Troll : public Enemy {
    public:
        Troll(std::string name)
            :   Enemy(
                    name,
                    TROLL_STATS.hp,
                    TROLL_STATS.attack,
                    TROLL_STATS.defense,
                    TROLL_STATS.expReward,
                    TROLL_STATS.goldReward
                ) {}
};