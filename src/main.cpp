#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>
#include <utility>
#include "enemies/goblin.h"
#include "enemies/skeleton.h"
#include "enemies/troll.h"
#include "enemies/goblin_chief.h"
#include "enemies/stone_golem.h"
#include "enemies/dark_necromancer.h"
#include "classes/rogue.h"
#include "enemy.h"

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
std::unique_ptr<Enemy> getRandomEnemy() {
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

void fightEnemy(Player& player, std::unique_ptr<Enemy> enemy) {
    int choice;
    unsigned short turn = 0;
    while (player.isAlive() && enemy->isAlive()) {
        player.printHpBar();
        enemy->printHpBar();

        std::cout << "\n1. Attack\n2. Flee\n> ";
        std::cin >> choice;

        if (choice == 1) {
            enemy->takeDamage(player.calculateDamage(*enemy));
            if (enemy->isAlive()) {
                player.takeDamage(enemy->calculateDamage(player));
                if (++turn % 3 == 0) {
                    auto* necro = dynamic_cast<DarkNecromancer*>(enemy.get());
                    if (necro) {
                        auto skeleton = necro->summonSkeleton();
                        std::cout << "Dark Necromancer summons a Skeleton!\n";
                        fightEnemy(player, std::move(skeleton));
                    }
                }
            }
        } else if (choice == 2) {
            std::cout << "You fled!\n";
            break;
        }

        if (!player.isAlive()) {
            std::cout << "You died! Enemy won!\n";
        }

        if (!enemy->isAlive()) {
            std::cout << "You won!!!\n";
            player.addExperience(enemy->getExpReward());
            std::cout << "You have " << player.getExperience() << " XP\n";
            player.addGold(enemy->getGoldReward());
            std::cout << "You have " << player.getGold() << " Gold\n";
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    Rogue player("Maarsu");

    for (int i = 0; i < 2; i++) {
        
        auto enemy = getRandomEnemy();

        fightEnemy(player, std::move(enemy));

        if (!player.isAlive()) { break; }
    }
    if (player.isAlive()) {
        fightEnemy(player, std::make_unique<GoblinChief>("Shaman"));
    }

    for (int i = 0 ; i < 3; i++) {
        auto enemy = getRandomEnemy();

        fightEnemy(player, std::move(enemy));
        
        if (!player.isAlive()) { break; }
    }
    if (player.isAlive()) {
        fightEnemy(player, std::make_unique<StoneGolem>("Stone Golem"));
    }
    if (player.isAlive()) {
        fightEnemy(player, std::make_unique<DarkNecromancer>("Malachar"));
    }
    return 0;
}
