#pragma once
#include "item.h"

class Weapon : public Item {
    public:
        Weapon() : Item("Iron Swork", ItemType::WEAPON) {};

        
};