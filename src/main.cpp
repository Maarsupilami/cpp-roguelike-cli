#include <cstdlib>
#include <ctime>
#include "enemies/goblin.h"
#include "classes/rogue.h"

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    int choice;
    Rogue player("Maarsu");
    Goblin goblin("Fallen");

    while (player.isAlive() && goblin.isAlive()) {
        player.printHpBar();
        goblin.printHpBar();

        std::cout << "\n1. Attack\n2. Flee\n> ";
        std::cin >> choice;

        if (choice == 1) {
            goblin.takeDamage(player.calculateDamage(goblin));
            if (goblin.isAlive()) {
                player.takeDamage(goblin.calculateDamage(player));
            }
        } else if (choice == 2) {
            std::cout << "You fled!\n";
            break;
        }

        if (!player.isAlive()) {
            std::cout << "You died! Enemy won!\n";
        }

        if (!goblin.isAlive()) {
            std::cout << "You won!!!\n";
        }

    }

    return 0;
}
