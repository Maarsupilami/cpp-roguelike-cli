#pragma once
#include "enemy.h"
#include "game_constants.h"

class StoneGolem : public Enemy{
    public:
        StoneGolem(std::string name)
            :   Enemy(
                    name,
                    STONE_GOLEM_HP,
                    STONE_GOLEM_ATTACK,
                    STONE_GOLEM_DEFENSE,
                    STONE_GOLEM_EXP_REWARD,
                    STONE_GOLEM_GOLD_REWARD
                ) {}
};