#include "Weapon.h"

Weapon::Weapon(int itemId, std::string itemName, int itemPrice, int minDmg, int maxDmg)
    : Item(itemId, itemName, itemPrice) {
    minDamage = minDmg;
    maxDamage = maxDmg;
}