#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    std::string name;
    std::string description;
    Location* north;
    Location* south;
    Location* east;
    Location* west;
    
    Location(std::string locName, std::string locDesc);
    void Display();
};

#endif