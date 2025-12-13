#include "Location.h"
#include "UI.h"
#include <iostream>

Location::Location(std::string locName, std::string locDesc) {
    name = locName;
    description = locDesc;
    north = nullptr;
    south = nullptr;
    east = nullptr;
    west = nullptr;
    monster = nullptr;
}

void Location::Display() {
    UI::PrintHeader(name);
    std::cout << UI::CYAN << description << UI::RESET << "\n";
    
    if (monster && monster->IsAlive()) {
        std::cout << "\n";
        monster->Display();
    }
}