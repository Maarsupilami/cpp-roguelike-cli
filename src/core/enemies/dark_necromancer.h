#pragma once
#include "enemy.h"
#include "game_constants.h"
#include "skeleton.h"
#include <memory>

class DarkNecromancer : public Enemy{
    public:
        DarkNecromancer(std::string name)
            :   Enemy(
                    name,
                    DARK_NECROMANCER_STATS.hp,
                    DARK_NECROMANCER_STATS.attack,
                    DARK_NECROMANCER_STATS.defense,
                    DARK_NECROMANCER_STATS.expReward,
                    DARK_NECROMANCER_STATS.goldReward
                ) {}
        
        std::unique_ptr<Enemy> summonSkeleton() {
            return std::make_unique<Skeleton>("Bone Warrior");
        }
};