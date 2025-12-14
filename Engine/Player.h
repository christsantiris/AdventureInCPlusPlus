#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Item.h"

class Player {
public:
    int hitPoints;
    int gold;
    std::string name;
    std::vector<Item*> inventory;
    
    Player(std::string playerName);
    void DisplayStats();
    void AddItem(Item* item);
    bool HasItem(int itemId);
    int GetItemCount(int itemId);
};

#endif