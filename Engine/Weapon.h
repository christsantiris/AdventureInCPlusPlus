#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    int minDamage;
    int maxDamage;
    
    Weapon(int itemId, std::string itemName, int itemPrice, int minDmg, int maxDmg);
};

#endif