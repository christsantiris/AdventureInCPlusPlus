#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
public:
    std::string name;
    int hitPoints;
    int maxDamage;
    int rewardGold;
    
    Monster(std::string monsterName, int hp, int damage, int gold);
    void Display();
    bool IsAlive();
};

#endif