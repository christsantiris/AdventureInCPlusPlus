#include "Player.h"
#include <iostream>

Player::Player(std::string playerName) {
    name = playerName;
    hitPoints = 10;
    gold = 20;
}

void Player::DisplayStats() {
    std::cout << "\n=== Player Stats ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "HP: " << hitPoints << std::endl;
    std::cout << "Gold: " << gold << std::endl;
}