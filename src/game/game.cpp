#include "game.h"
#include "combat.h"
#include <ctime>
#include <memory>
#include <random>
#include <utility>
#include "classes/warrior.h"
#include "classes/mage.h"
#include "classes/rogue.h"
#include "enemies/goblin.h"
#include "enemies/skeleton.h"
#include "enemies/troll.h"
#include "enemies/goblin_chief.h"
#include "enemies/stone_golem.h"
#include "enemies/dark_necromancer.h" // needed for dungeonLoop final boss

/*
 * NOTE: Raw pointer alternative (pre-C++11 / older compilers):
 *
 *   Enemy* getRandomEnemy() {
 *       int r = rand() % 3;
 *       if (r == 0) return new Goblin("Goblin");
 *       if (r == 1) return new Skeleton("Skeleton");
 *       return new Troll("Troll");
 *   }
 *
 *   After use, manually free memory:
 *   delete enemy;
 *
 *   If you forget delete -> memory leak.
 *   unique_ptr handles this automatically.
 */
std::unique_ptr<Enemy> Game::getRandomEnemy() {
    std::unique_ptr<Enemy> enemy;
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0,(int)EnemyType::COUNT - 1);

    EnemyType r = static_cast<EnemyType>(dist(rng));
    switch (r) {
        case EnemyType::GOBLIN:
            enemy = std::make_unique<Goblin>("Fallen");
            break;
        case EnemyType::SKELETON:
            enemy = std::make_unique<Skeleton>("Bone Warrior");
            break;
        case EnemyType::TROLL:
            enemy = std::make_unique<Troll>("Mauler");
            break;
        default:
            enemy = std::make_unique<Goblin>("Fallen");
    };
    return enemy;
}

void Game::showInventoryMenu() {
    if (player->getInventory().empty()) {
        std::cout << "Inventory is empty!" << "\n";
        return;
    };
    int itemChoice;
    const auto& inventory = player->getInventory();
    std::cout << "0. Cancel\n";
    for (int i = 0; i < (int)inventory.size(); i++) {
        std::cout << i + 1 << ". " << inventory[i]->getName();
        if (!inventory[i]->getDescription().empty()) std::cout << " " << inventory[i]->getDescription();
        if (inventory[i]->getQuantity() > 1) std::cout << " x" << inventory[i]->getQuantity();
        std::cout << "\n";
    }
    std::cout << "Choose item: ";
    std::cin >> itemChoice;
    if (itemChoice == 0) { return; }
    player->useItem(itemChoice - 1, nullptr);
};

void Game::fightEnemy(std::unique_ptr<Enemy> enemy) {
    int choice;
    unsigned short turn = 0;

    std::cout << "\n--- " << enemy->getName() << " appears! ---\n";

    while (player->isAlive() && enemy->isAlive()) {
        std::cout << "\n─────────────────────────\n";
        player->printHpBar();
        enemy->printHpBar();

        std::cout << "\n1. Attack\n2. Use item\n3. Flee\n> ";
        std::cin >> choice;

        if (choice == 1) {
            auto result = executeAttack(*player, *enemy, turn);
            std::cout << "  You hit " << enemy->getName() << " for " << result.damageDealt << " damage.\n";
            if (result.damageTaken > 0) {
                std::cout << "  " << enemy->getName() << " hits you for " << result.damageTaken << " damage.\n";
            }
            if (result.summonedEnemy) {
                std::cout << "\n*** Dark Necromancer summons a Skeleton! ***\n";
                fightEnemy(std::move(result.summonedEnemy));
            }
        } else if (choice == 2) {
            showInventoryMenu();
        } else if (choice == 3) {
            std::cout << "\nYou fled!\n";
            break;
        }

        if (!player->isAlive()) {
            std::cout << "\n=== You died! Game over. ===\n";
        }

        if (!enemy->isAlive()) {
            std::cout << "\n> " << enemy->getName() << " defeated!\n";
            player->addExperience(enemy->getExpReward());
            player->addGold(enemy->getGoldReward());
            std::cout << "  XP: " << player->getExperience()
                      << " | Gold: " << player->getGold()
                      << " | Level: " << player->getLevel() << "\n";

            auto item = enemy->drop();
            if (item) {
                std::cout << "  Dropped: " << item->getName() << "!\n";
                player->addItem(std::move(item));
            };
        }
    }
}

void Game::choosePlayer() {
    std::string name;
    int choice = -1;

    std::cout << "Please type your name: " << "\n";
    std::cin >> name;

    while (choice <= 0 || static_cast<PlayerType>(choice) > PlayerType::COUNT) {
        std::cout << "Please choose a cast!" << "\n";
        std::cout << "\t1. Warrior" << "\n";
        std::cout << "\t2. Mage" << "\n";
        std::cout << "\t3. Rogue" << "\n";
        std::cout << "Enter the corresponding number: ";
        std::cin >> choice;
    }

    PlayerType c = static_cast<PlayerType>(choice - 1);
    switch (c) {
        case PlayerType::WARRIOR:
            player = std::make_unique<Warrior>(name);
            break;
        case PlayerType::MAGE:
            player = std::make_unique<Mage>(name);
            break;
        case PlayerType::ROGUE:
            player = std::make_unique<Rogue>(name);
            break;
        default:
            player = std::make_unique<Rogue>(name);
    }
}

void Game::dungeonLoop() {
    std::cout << "\n========== DUNGEON LEVEL 1 ==========\n";
    for (int i = 0; i < 2; i++) {
        auto enemy = getRandomEnemy();
        fightEnemy(std::move(enemy));
        if (!player->isAlive()) { break; }
        showInventoryMenu();
    }
    if (player->isAlive()) {
        std::cout << "\n--- MINI-BOSS ---\n";
        fightEnemy(std::make_unique<GoblinChief>("Shaman"));
    }

    if (player->isAlive()) {
        std::cout << "\n========== DUNGEON LEVEL 2 ==========\n";
        for (int i = 0 ; i < 3; i++) {
            auto enemy = getRandomEnemy();
            fightEnemy(std::move(enemy));
            if (!player->isAlive()) { break; }
            showInventoryMenu();
        }
    }
    if (player->isAlive()) {
        std::cout << "\n--- BOSS ---\n";
        fightEnemy(std::make_unique<StoneGolem>("Stone Golem"));
    }

    if (player->isAlive()) {
        std::cout << "\n========== DUNGEON LEVEL 3 ==========\n";
        std::cout << "--- FINAL BOSS ---\n";
        fightEnemy(std::make_unique<DarkNecromancer>("Malachar"));
    }

    if (player->isAlive()) {
        std::cout << "\n========== YOU CLEARED THE DUNGEON! ==========\n";
        std::cout << "Final stats — Level: " << player->getLevel()
                  << " | XP: " << player->getExperience()
                  << " | Gold: " << player->getGold() << "\n";
    }
}

void Game::run() {
    srand(time(nullptr));
    choosePlayer();
    dungeonLoop();
}
