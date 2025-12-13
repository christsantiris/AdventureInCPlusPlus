#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    int hitPoints;
    int gold;
    std::string name;
    
    Player(std::string playerName);
    void DisplayStats();
};

#endif