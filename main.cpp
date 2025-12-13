#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Location.h"
#include "Monster.h"

int main() {
    srand(time(0)); // Seed random number generator
    
    std::cout << "Adventures in C++" << std::endl;
    std::cout << "Welcome Player!" << std::endl;
    std::cout << "\nWhat is your name? ";
    
    std::string playerName;
    std::getline(std::cin, playerName);
    
    Player player(playerName);
    
    // Create locations
    Location home("Home", "Your house. Today is the day. You are embarking on the quest you have been planning.");
    Location townSquare("Town Square", "There is a lot of activity. You see a fountain and several shops.");
    Location forest("Forest", "A dark forest. You hear strange noises.");
    
    // Create a monster
    Monster rat("Giant Rat", 5, 3, 5);
    
    // Link locations together
    home.north = &townSquare;
    townSquare.south = &home;
    townSquare.east = &forest;
    forest.west = &townSquare;
    
    // Put monster in forest
    forest.monster = &rat;
    
    // Start at home
    Location* currentLocation = &home;
    currentLocation->Display();
    player.DisplayStats();
    
    // Game loop
    bool playing = true;
    while (playing) {
        // Check if there's a monster to fight
        if (currentLocation->monster && currentLocation->monster->IsAlive()) {
            std::cout << "\n*** COMBAT ***" << std::endl;
            std::cout << "F - Fight" << std::endl;
            std::cout << "R - Run Away" << std::endl;
            std::cout << "Choice: ";
            
            char combatChoice;
            std::cin >> combatChoice;
            
            if (combatChoice == 'F' || combatChoice == 'f') {
                // Player attacks
                int damage = rand() % 5 + 1; // 1-5 damage
                currentLocation->monster->hitPoints -= damage;
                std::cout << "You hit the " << currentLocation->monster->name 
                         << " for " << damage << " damage!" << std::endl;
                
                if (currentLocation->monster->IsAlive()) {
                    // Monster attacks back
                    int monsterDamage = rand() % currentLocation->monster->maxDamage + 1;
                    player.hitPoints -= monsterDamage;
                    std::cout << "The " << currentLocation->monster->name 
                             << " hits you for " << monsterDamage << " damage!" << std::endl;
                    
                    if (player.hitPoints <= 0) {
                        std::cout << "\n*** YOU DIED! ***" << std::endl;
                        std::cout << "Game Over!" << std::endl;
                        playing = false;
                    }
                } else {
                    std::cout << "\nYou defeated the " << currentLocation->monster->name << "!" << std::endl;
                    player.gold += currentLocation->monster->rewardGold;
                    std::cout << "You found " << currentLocation->monster->rewardGold << " gold!" << std::endl;
                }
                
                player.DisplayStats();
                continue;
            } else if (combatChoice == 'R' || combatChoice == 'r') {
                std::cout << "You run away!" << std::endl;
                currentLocation = &home;
                currentLocation->Display();
                player.DisplayStats();
                continue;
            }
        }
        
        // Normal movement
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
        } else if (choice == 'E' || choice == 'e') {
            if (currentLocation->east) {
                currentLocation = currentLocation->east;
                currentLocation->Display();
                player.DisplayStats();
            } else {
                std::cout << "You can't go that way!" << std::endl;
            }
        } else if (choice == 'W' || choice == 'w') {
            if (currentLocation->west) {
                currentLocation = currentLocation->west;
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