#include "Location.h"
#include <iostream>

Location::Location(std::string locName, std::string locDesc) {
    name = locName;
    description = locDesc;
    north = nullptr;
    south = nullptr;
    east = nullptr;
    west = nullptr;
}

void Location::Display() {
    std::cout << "\n=== " << name << " ===" << std::endl;
    std::cout << description << std::endl;
}