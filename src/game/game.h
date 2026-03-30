#pragma once
#include <memory>
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