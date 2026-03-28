#pragma once
#include "enemy.h"
#include "game_constants.h"

class DarkNecromancer : public Enemy{
    public:
        DarkNecromancer(std::string name)
            :   Enemy(
                    name,
                    DARK_NECROMANCER_HP,
                    DARK_NECROMANCER_ATTACK,
                    DARK_NECROMANCER_DEFENSE,
                    DARK_NECROMANCER_EXP_REWARD,
                    DARK_NECROMANCER_GOLD_REWARD
                ) {}
};