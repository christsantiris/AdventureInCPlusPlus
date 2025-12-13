#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include "Monster.h"

class Location {
public:
    std::string name;
    std::string description;
    Location* north;
    Location* south;
    Location* east;
    Location* west;
    Monster* monster;
    
    Location(std::string locName, std::string locDesc);
    void Display();
};

#endif