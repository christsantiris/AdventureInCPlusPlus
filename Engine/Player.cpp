#include "Player.h"
#include "UI.h"
#include <iostream>

Player::Player(std::string playerName) {
    name = playerName;
    hitPoints = 10;
    gold = 20;
}

void Player::DisplayStats() {
    std::cout << "\n" << UI::GREEN << UI::BOLD << "═══ PLAYER STATS ═══" << UI::RESET << std::endl;
    std::cout << UI::CYAN << "Name: " << UI::RESET << name << std::endl;
    std::cout << UI::GREEN << "HP:   " << UI::RESET << hitPoints << std::endl;
    std::cout << UI::YELLOW << "Gold: " << UI::RESET << gold << std::endl;
    UI::PrintSeparator();
}