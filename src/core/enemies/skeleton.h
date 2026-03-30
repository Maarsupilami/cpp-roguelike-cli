#pragma once
#include "enemy.h"
#include "game_constants.h"

class Skeleton : public Enemy{
    public:
        Skeleton(std::string name)
            :   Enemy(
                    name,
                    SKELETON_STATS.hp,
                    SKELETON_STATS.attack,
                    SKELETON_STATS.defense,
                    SKELETON_STATS.expReward,
                    SKELETON_STATS.goldReward
                ) {}
};