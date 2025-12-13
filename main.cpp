#include <iostream>
#include <string>
#include "Player.h"
#include "Location.h"

int main() {
    std::cout << "Adventures in C++" << std::endl;
    std::cout << "Welcome Player!" << std::endl;
    std::cout << "\nWhat is your name? ";
    
    std::string playerName;
    std::getline(std::cin, playerName);
    
    Player player(playerName);
    
    // Create locations
    Location home("Home", "Your house. Today is the day. You are embarking on the quest you have been planning.");
    Location townSquare("Town Square", "There is a lot of activity. You see a fountain and several shops.");
    
    // Link locations together
    home.north = &townSquare;
    townSquare.south = &home;
    
    // Start at home
    Location* currentLocation = &home;
    currentLocation->Display();
    player.DisplayStats();
    
    // Simple movement loop
    bool playing = true;
    while (playing) {
        std::cout << "\nWhere do you want to go?" << std::endl;
        if (currentLocation->north) std::cout << "N - North" << std::endl;
        if (currentLocation->south) std::cout << "S - South" << std::endl;
        if (currentLocation->east) std::cout << "E - East" << std::endl;
        if (currentLocation->west) std::cout << "W - West" << std::endl;
        std::cout << "Q - Quit" << std::endl;
        
        std::cout << "\nChoice: ";
        char choice;
        std::cin >> choice;
        
        if (choice == 'N' || choice == 'n') {
            if (currentLocation->north) {
                currentLocation = currentLocation->north;
                currentLocation->Display();
                player.DisplayStats();
            } else {
                std::cout << "You can't go that way!" << std::endl;
            }
        } else if (choice == 'S' || choice == 's') {
            if (currentLocation->south) {
                currentLocation = currentLocation->south;
                currentLocation->Display();
                player.DisplayStats();
            } else {
                std::cout << "You can't go that way!" << std::endl;
            }
        } else if (choice == 'Q' || choice == 'q') {
            std::cout << "Thanks for playing!" << std::endl;
            playing = false;
        }
    }
    
    return 0;
}