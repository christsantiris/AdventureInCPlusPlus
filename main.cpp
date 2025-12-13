#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Location.h"
#include "Monster.h"
#include "UI.h"

int main() {
    srand(time(0)); // Seed random number generator
    
    UI::ClearScreen();
    UI::PrintHeader("ADVENTURE RPG");
    
    std::cout << "\n" << UI::CYAN << "What is your name? " << UI::RESET;
    std::string playerName;
    std::getline(std::cin, playerName);
    
    Player player(playerName);
    
    // Create locations
    Location home("Home", "Your cozy house. You're bored and ready for adventure.");
    Location townSquare("Town Square", "The bustling center of town. You see a fountain.");
    Location forest("Forest", "A dark forest. You hear strange noises.");
    
    // Create a monster
    Monster rat("Rat", 5, 3, 5);
    
    // Link locations together
    home.north = &townSquare;
    townSquare.south = &home;
    townSquare.east = &forest;
    forest.west = &townSquare;
    
    // Put monster in forest
    forest.monster = &rat;
    
    // Start at home
    Location* currentLocation = &home;
    
    // Game loop
    bool playing = true;
    while (playing) {
        UI::ClearScreen();
        currentLocation->Display();
        player.DisplayStats();
        
        // Check if there's a monster to fight
        if (currentLocation->monster && currentLocation->monster->IsAlive()) {
            std::cout << "\n" << UI::RED << UI::BOLD << "═══ COMBAT ═══" << UI::RESET << std::endl;
            std::cout << UI::YELLOW << "F" << UI::RESET << " - Fight\n";
            std::cout << UI::YELLOW << "R" << UI::RESET << " - Run Away\n";
            std::cout << "\n" << UI::CYAN << "Choice: " << UI::RESET;
            
            char combatChoice;
            std::cin >> combatChoice;
            
            if (combatChoice == 'F' || combatChoice == 'f') {
                // Player attacks
                int damage = rand() % 5 + 1; // 1-5 damage
                currentLocation->monster->hitPoints -= damage;
                
                UI::ClearScreen();
                currentLocation->Display();
                UI::PrintCombatMessage("You hit the " + currentLocation->monster->name + 
                                     " for " + std::to_string(damage) + " damage!");
                
                if (currentLocation->monster->IsAlive()) {
                    // Monster attacks back
                    int monsterDamage = rand() % currentLocation->monster->maxDamage + 1;
                    player.hitPoints -= monsterDamage;
                    UI::PrintCombatMessage("The " + currentLocation->monster->name + 
                                         " hits you for " + std::to_string(monsterDamage) + " damage!");
                    
                    if (player.hitPoints <= 0) {
                        std::cout << "\n";
                        UI::PrintErrorMessage("YOU DIED!");
                        std::cout << UI::RED << UI::BOLD << "\nGAME OVER!" << UI::RESET << std::endl;
                        playing = false;
                    }
                } else {
                    std::cout << "\n";
                    UI::PrintSuccessMessage("You defeated the " + currentLocation->monster->name + "!");
                    player.gold += currentLocation->monster->rewardGold;
                    UI::PrintSuccessMessage("You found " + std::to_string(currentLocation->monster->rewardGold) + " gold!");
                }
                
                player.DisplayStats();
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
                continue;
            } else if (combatChoice == 'R' || combatChoice == 'r') {
                UI::PrintErrorMessage("You run away!");
                currentLocation = &home;
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
                continue;
            }
        }
        
        // Normal movement
        std::cout << "\n" << UI::GREEN << UI::BOLD << "═══ ACTIONS ═══" << UI::RESET << std::endl;
        if (currentLocation->north) std::cout << UI::YELLOW << "N" << UI::RESET << " - North\n";
        if (currentLocation->south) std::cout << UI::YELLOW << "S" << UI::RESET << " - South\n";
        if (currentLocation->east) std::cout << UI::YELLOW << "E" << UI::RESET << " - East\n";
        if (currentLocation->west) std::cout << UI::YELLOW << "W" << UI::RESET << " - West\n";
        std::cout << UI::YELLOW << "Q" << UI::RESET << " - Quit\n";
        
        std::cout << "\n" << UI::CYAN << "Choice: " << UI::RESET;
        char choice;
        std::cin >> choice;
        
        if (choice == 'N' || choice == 'n') {
            if (currentLocation->north) {
                currentLocation = currentLocation->north;
            } else {
                UI::PrintErrorMessage("You can't go that way!");
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == 'S' || choice == 's') {
            if (currentLocation->south) {
                currentLocation = currentLocation->south;
            } else {
                UI::PrintErrorMessage("You can't go that way!");
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == 'E' || choice == 'e') {
            if (currentLocation->east) {
                currentLocation = currentLocation->east;
            } else {
                UI::PrintErrorMessage("You can't go that way!");
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == 'W' || choice == 'w') {
            if (currentLocation->west) {
                currentLocation = currentLocation->west;
            } else {
                UI::PrintErrorMessage("You can't go that way!");
                std::cout << "\n" << UI::CYAN << "Press Enter to continue..." << UI::RESET;
                std::cin.ignore();
                std::cin.get();
            }
        } else if (choice == 'Q' || choice == 'q') {
            UI::ClearScreen();
            UI::PrintHeader("THANKS FOR PLAYING!");
            playing = false;
        }
    }
    
    return 0;
}