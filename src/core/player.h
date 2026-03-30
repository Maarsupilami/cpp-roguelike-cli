#pragma once
#include "character.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include "item.h"
#include "items/weapon.h"

enum class PlayerType {
    WARRIOR,
    MAGE,
    ROGUE,
    COUNT
};

enum class SlotType {
    MainHand,
    OffHand
};

struct EquipSlots {
    std::unique_ptr<Weapon> mainHand;
    std::unique_ptr<Weapon> offHand;
};

class Player : public Character {
    protected:
        EquipSlots equipment;
        std::vector<std::unique_ptr<Item>> inventory;
        int experience;
        unsigned int gold;
        float critChance;

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

        void addItem(std::unique_ptr<Item> item){
            inventory.push_back(std::move(item));
        }

        bool equip(const std::string& weaponName, SlotType slot) {
            // Search in the inventory
            auto it = std::find_if(inventory.begin(), inventory.end(),
                [&weaponName](const std::unique_ptr<Item>& item) {
                    return item->getName() == weaponName;
                });
            if (it == inventory.end()) { return false; }

            // Check if it is a weapon type or not
            Weapon* w = dynamic_cast<Weapon*>(it->get());
            if (!w) { return false; }

            // Take out from the inventory
            std::unique_ptr<Item> taken = std::move(*it);
            inventory.erase(it);

            // Slot
            std::unique_ptr<Weapon>& targetSlot = 
                (slot == SlotType::MainHand) ? equipment.mainHand : equipment.offHand;
            
            // If anything was in the slot, put back to the inventory
            if (targetSlot) { inventory.push_back(std::move(targetSlot)); }

            // Put the new weapon it
            targetSlot = std::unique_ptr<Weapon>(static_cast<Weapon*>(taken.release()));
            return true;
        }

        Weapon* getEquipped(SlotType slot) const {
            return (slot == SlotType::MainHand)
                ? equipment.mainHand.get()
                : equipment.offHand.get();
        }

        unsigned int getGold() const { return gold; }
        void addGold(unsigned int amount) {
            gold += amount;
        }

        const std::vector<std::unique_ptr<Item>>& getInventory() const { return inventory; }
};