#include "Monster.h"
#include "UI.h"
#include <iostream>

Monster::Monster(std::string monsterName, int hp, int damage, int gold) {
    name = monsterName;
    hitPoints = hp;
    maxDamage = damage;
    rewardGold = gold;
}

void Monster::Display() {
    std::cout << UI::RED << UI::BOLD << "⚠ DANGER: " << name << " blocks your path!" << UI::RESET << std::endl;
    std::cout << UI::RED << "HP: " << hitPoints << UI::RESET << std::endl;
}

bool Monster::IsAlive() {
    return hitPoints > 0;
}