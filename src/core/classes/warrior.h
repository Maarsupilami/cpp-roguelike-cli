#pragma once
#include "player.h"
#include "game_constants.h"

class Warrior : public Player {
    public:
        Warrior(std::string name)
            :   Player(
                    name,
                    WARRIOR_HP,
                    WARRIOR_ATTACK,
                    WARRIOR_DEFENSE,
                    WARRIOR_CRIT) {}
};