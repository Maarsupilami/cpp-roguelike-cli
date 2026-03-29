#pragma once
#include "character.h"
#include <vector>
#include <string>
#include "item.h"

enum class PlayerType {
    WARRIOR,
    MAGE,
    ROGUE,
    COUNT
};

class Player : public Character {
    protected:
        int experience;
        unsigned int gold;
        float critChance;
        std::vector<Item> inventory;

        virtual void levelUp() {
            level++;
            maxHp += 10;
            hp = maxHp;
            attackPower += 2;
            defense += 1;
            std::cout << name << " leveled up! Now level " << level << "!\n";
        }

    public:
        Player(std::string name, int hp, int attackPower, int defense, float critChance)
            :   Character(name, hp, attackPower, defense),
                experience(0),
                gold(0),
                critChance(critChance) {}
        
        int getExperience() const { return experience; }
        void addExperience(int amount) {
            experience += amount;
            if (experience >= 100 * level) {
                levelUp();
            }
        }

        void addItem(const Item& item){
            inventory.push_back(item);
        }

        unsigned int getGold() const { return gold; }
        void addGold(unsigned int amount) {
            gold += amount;
        }

        const std::vector<Item>& getInventory() const { return inventory; }
};