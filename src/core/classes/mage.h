#pragma once
#include "player.h"
#include "game_constants.h"

class Mage : public Player {
    private:
        void levelUp() override {
            level++;
            maxHp += 7;
            hp = maxHp;
            attackPower += 4;
            defense += 1;
            std::cout << name << " leveled up! Now level " << level << "!\n"; 
        }

    public:
        Mage(std::string name)
            :   Player(
                    name,
                    MAGE_HP,
                    MAGE_ATTACK,
                    MAGE_DEFENSE,
                    MAGE_CRIT) {}
};