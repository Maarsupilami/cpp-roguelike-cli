#pragma once
#include "player.h"
#include "game_constants.h"

class Rogue : public Player {
    public:
        Rogue(std::string name)
            :   Player(
                    name,
                    ROGUE_HP,
                    ROGUE_ATTACK,
                    ROGUE_DEFENSE,
                    ROGUE_CRIT) {}
};