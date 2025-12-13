#include "Monster.h"
#include <iostream>

Monster::Monster(std::string monsterName, int hp, int damage, int gold) {
    name = monsterName;
    hitPoints = hp;
    maxDamage = damage;
    rewardGold = gold;
}

void Monster::Display() {
    std::cout << "\n*** " << name << " appears! ***" << std::endl;
    std::cout << "HP: " << hitPoints << std::endl;
}

bool Monster::IsAlive() {
    return hitPoints > 0;
}