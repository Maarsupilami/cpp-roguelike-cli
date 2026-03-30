#pragma once
#include <memory>
#include "player.h"
#include "enemy.h"

// Holds the outcome of a single attack turn.
// Separating combat logic from I/O makes it unit-testable
// without simulating std::cin.
struct AttackResult {
    int damageDealt = 0;
    int damageTaken = 0;            // 0 if enemy died before counter-attack
    std::unique_ptr<Enemy> summonedEnemy = nullptr;
};

AttackResult executeAttack(Player& player, Enemy& enemy, unsigned short& turn);
