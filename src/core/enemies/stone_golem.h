#pragma once
#include "enemy.h"
#include "game_constants.h"

class StoneGolem : public Enemy{
    public:
        StoneGolem(std::string name)
            :   Enemy(
                    name,
                    STONE_GOLEM_STATS.hp,
                    STONE_GOLEM_STATS.attack,
                    STONE_GOLEM_STATS.defense,
                    STONE_GOLEM_STATS.expReward,
                    STONE_GOLEM_STATS.goldReward
                ) {}
};