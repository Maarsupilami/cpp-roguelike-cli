#pragma once
#include "player.h"
#include "game_constants.h"

class Mage : public Player {
    public:
        Mage(std::string name)
            :   Player(
                    name,
                    MAGE_HP,
                    MAGE_ATTACK,
                    MAGE_DEFENSE,
                    MAGE_CRIT) {}
};