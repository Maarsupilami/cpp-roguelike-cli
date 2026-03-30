#pragma once
#include "item.h"
#include "player.h"

class Enemy;
class HealthPotion : public Item {
    public:
        HealthPotion() : Item("Health Potion", ItemType::POTION){};

        void use(Player& player, Enemy* enemy = nullptr) override {
            player.heal(30);
        }
};