#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Item.h"

class Monster {
public:
    std::string name;
    int hitPoints;
    int maxDamage;
    int rewardGold;
    Item* lootItem;
    
    Monster(std::string monsterName, int hp, int damage, int gold);
    void Display();
    bool IsAlive();
};

#endif