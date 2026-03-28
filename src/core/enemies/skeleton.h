#pragma once
#include "enemy.h"
#include "game_constants.h"

class Skeleton : public Enemy{
    public:
        Skeleton(std::string name)
            :   Enemy(
                    name,
                    SKELETON_HP,
                    SKELETON_ATTACK,
                    SKELETON_DEFENSE,
                    SKELETON_EXP_REWARD,
                    SKELETON_GOLD_REWARD
                ) {}
};