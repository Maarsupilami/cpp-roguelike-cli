#pragma once
#include <memory>
#include "classes/warrior.h"
#include "classes/mage.h"
#include "classes/rogue.h"
#include "enemies/goblin.h"
#include "enemies/skeleton.h"
#include "enemies/troll.h"
#include "enemies/goblin_chief.h"
#include "enemies/stone_golem.h"
#include "enemies/dark_necromancer.h"
#include "player.h"
#include "enemy.h"

class Game {
    private:
        std::unique_ptr<Player> player;

        void choosePlayer();
        std::unique_ptr<Enemy> getRandomEnemy();
        void fightEnemy(std::unique_ptr<Enemy> enemy);
        void dungeonLoop();
    
    public:
        void run();
};