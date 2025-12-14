#include "Player.h"
#include "UI.h"
#include <iostream>
#include <algorithm>

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

void Player::AddItem(Item* item) {
    inventory.push_back(item);
}

bool Player::HasItem(int itemId) {
    return std::any_of(inventory.begin(), inventory.end(),
        [itemId](Item* item) { return item->id == itemId; });
}

int Player::GetItemCount(int itemId) {
    return std::count_if(inventory.begin(), inventory.end(),
        [itemId](Item* item) { return item->id == itemId; });
}