#include "game.h"
#include <ctime>
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
#include "enemies/dark_necromancer.h"

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

void Game::fightEnemy(std::unique_ptr<Enemy> enemy) {
    int choice;
    unsigned short turn = 0;

    std::cout << "\n--- " << enemy->getName() << " appears! ---\n";

    while (player->isAlive() && enemy->isAlive()) {
        std::cout << "\n";
        player->printHpBar();
        enemy->printHpBar();

        std::cout << "\n1. Attack\n2. Flee\n> ";
        std::cin >> choice;

        if (choice == 1) {
            enemy->takeDamage(player->calculateDamage(*enemy));
            if (enemy->isAlive()) {
                player->takeDamage(enemy->calculateDamage(*player));
                if (++turn % 3 == 0) {
                    auto* necro = dynamic_cast<DarkNecromancer*>(enemy.get());
                    if (necro) {
                        auto skeleton = necro->summonSkeleton();
                        std::cout << "\n*** Dark Necromancer summons a Skeleton! ***\n";
                        fightEnemy(std::move(skeleton));
                    }
                }
            }
        } else if (choice == 2) {
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
