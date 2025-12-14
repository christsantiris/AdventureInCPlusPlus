#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "Player.h"
#include "Location.h"
#include "Monster.h"
#include "Item.h"

int main(int argc, char* argv[]) {
    srand(time(0));
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Adventure RPG",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN
    );
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    
    // Game setup
    std::string playerName = "Hero";
    bool nameEntered = false;
    char nameBuffer[128] = "";
    
    Player* player = nullptr;
    
    // Create items
    Item ratTail(1, "Rat Tail", 5);
    Item snakeFang(2, "Snake Fang", 10);
    Item healthPotion(3, "Health Potion", 15);
    
    // Create locations
    Location home("Home", "Your cozy house. You're bored and ready for adventure.");
    Location townSquare("Town Square", "The bustling center of town. You see a fountain and some shops.");
    Location forest("Forest", "A dark forest. You hear strange noises.");
    
    // Create monsters
    Monster rat("Rat", 5, 3, 5);
    rat.lootItem = &ratTail;
    
    // Link locations
    home.north = &townSquare;
    townSquare.south = &home;
    townSquare.east = &forest;
    forest.west = &townSquare;
    forest.monster = &rat;
    
    Location* currentLocation = &home;
    std::string combatLog = "";
    
    // Main loop
    bool running = true;
    SDL_Event event;
    
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        // Start ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        // Name entry screen
        if (!nameEntered) {
            ImGui::SetNextWindowPos(ImVec2(440, 300));
            ImGui::SetNextWindowSize(ImVec2(400, 150));
            ImGui::Begin("Welcome to Adventure RPG", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            ImGui::Text("What is your name?");
            ImGui::InputText("##name", nameBuffer, 128);
            
            if (ImGui::Button("Start Adventure", ImVec2(120, 40))) {
                if (strlen(nameBuffer) > 0) {
                    playerName = std::string(nameBuffer);
                    player = new Player(playerName);
                    nameEntered = true;
                }
            }
            
            ImGui::End();
        } else {
            // Main game UI
            
            // Player Stats Window
            ImGui::SetNextWindowPos(ImVec2(10, 10));
            ImGui::SetNextWindowSize(ImVec2(300, 150));
            ImGui::Begin("Player Stats", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 1.0f, 1.0f), "Name: %s", player->name.c_str());
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "HP: %d", player->hitPoints);
            ImGui::TextColored(ImVec4(1.0f, 0.85f, 0.0f, 1.0f), "Gold: %d", player->gold);
            
            ImGui::End();
            
            // Inventory Window
            ImGui::SetNextWindowPos(ImVec2(10, 170));
            ImGui::SetNextWindowSize(ImVec2(300, 250));
            ImGui::Begin("Inventory", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            if (player->inventory.empty()) {
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Empty");
            } else {
                // Count items
                std::map<int, int> itemCounts;
                for (Item* item : player->inventory) {
                    itemCounts[item->id]++;
                }
                
                // Display unique items with counts
                for (auto& pair : itemCounts) {
                    Item* item = nullptr;
                    for (Item* i : player->inventory) {
                        if (i->id == pair.first) {
                            item = i;
                            break;
                        }
                    }
                    if (item) {
                        ImGui::BulletText("%s x%d", item->name.c_str(), pair.second);
                    }
                }
            }
            
            ImGui::End();
            
            // Location Window
            ImGui::SetNextWindowPos(ImVec2(320, 10));
            ImGui::SetNextWindowSize(ImVec2(600, 200));
            ImGui::Begin("Location", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 1.0f, 1.0f), "%s", currentLocation->name.c_str());
            ImGui::Separator();
            ImGui::TextWrapped("%s", currentLocation->description.c_str());
            
            if (currentLocation->monster && currentLocation->monster->IsAlive()) {
                ImGui::Separator();
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "DANGER: %s blocks your path!", 
                                 currentLocation->monster->name.c_str());
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "HP: %d", 
                                 currentLocation->monster->hitPoints);
            }
            
            ImGui::End();
            
            // Actions Window
            ImGui::SetNextWindowPos(ImVec2(930, 10));
            ImGui::SetNextWindowSize(ImVec2(340, 300));
            ImGui::Begin("Actions", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            // Combat actions
            if (currentLocation->monster && currentLocation->monster->IsAlive()) {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "COMBAT");
                ImGui::Separator();
                
                if (ImGui::Button("Fight", ImVec2(150, 40))) {
                    int damage = rand() % 5 + 1;
                    currentLocation->monster->hitPoints -= damage;
                    combatLog = "You hit the " + currentLocation->monster->name + 
                               " for " + std::to_string(damage) + " damage!\n";
                    
                    if (currentLocation->monster->IsAlive()) {
                        int monsterDamage = rand() % currentLocation->monster->maxDamage + 1;
                        player->hitPoints -= monsterDamage;
                        combatLog += "The " + currentLocation->monster->name + 
                                   " hits you for " + std::to_string(monsterDamage) + " damage!";
                        
                        if (player->hitPoints <= 0) {
                            combatLog += "\n\nYOU DIED! Game Over.";
                        }
                    } else {
                        combatLog += "You defeated the " + currentLocation->monster->name + "!\n";
                        player->gold += currentLocation->monster->rewardGold;
                        combatLog += "You found " + std::to_string(currentLocation->monster->rewardGold) + " gold!";
                        
                        // Drop loot
                        if (currentLocation->monster->lootItem) {
                            player->AddItem(currentLocation->monster->lootItem);
                            combatLog += "\nYou looted: " + currentLocation->monster->lootItem->name;
                        }
                    }
                }
                
                if (ImGui::Button("Run Away", ImVec2(150, 40))) {
                    currentLocation = &home;
                    combatLog = "You ran away to safety!";
                }
            } else {
                // Movement actions
                ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "MOVEMENT");
                ImGui::Separator();
                
                if (currentLocation->north && ImGui::Button("Go North", ImVec2(150, 40))) {
                    currentLocation = currentLocation->north;
                    combatLog = "";
                }
                
                if (currentLocation->south && ImGui::Button("Go South", ImVec2(150, 40))) {
                    currentLocation = currentLocation->south;
                    combatLog = "";
                }
                
                if (currentLocation->east && ImGui::Button("Go East", ImVec2(150, 40))) {
                    currentLocation = currentLocation->east;
                    combatLog = "";
                }
                
                if (currentLocation->west && ImGui::Button("Go West", ImVec2(150, 40))) {
                    currentLocation = currentLocation->west;
                    combatLog = "";
                }
            }
            
            ImGui::Separator();
            ImGui::Spacing();
            
            // Quit button (always visible)
            if (ImGui::Button("Quit Game", ImVec2(150, 40))) {
                running = false;
            }
            
            ImGui::End();
            
            // Combat Log Window
            ImGui::SetNextWindowPos(ImVec2(320, 220));
            ImGui::SetNextWindowSize(ImVec2(600, 200));
            ImGui::Begin("Messages", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            
            ImGui::TextWrapped("%s", combatLog.c_str());
            
            ImGui::End();
        }
        
        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
    
    // Cleanup
    if (player) delete player;
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}