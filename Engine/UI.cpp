#include "UI.h"
#include <iostream>

// Color codes
const std::string UI::RESET = "\033[0m";
const std::string UI::RED = "\033[31m";
const std::string UI::GREEN = "\033[32m";
const std::string UI::YELLOW = "\033[33m";
const std::string UI::BLUE = "\033[34m";
const std::string UI::CYAN = "\033[36m";
const std::string UI::MAGENTA = "\033[35m";
const std::string UI::BOLD = "\033[1m";

void UI::ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UI::PrintHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << CYAN << BOLD << "╔════════════════════════════════════════════╗\n";
    std::cout << "║  " << title;
    
    // Add padding to center the title
    int padding = 42 - title.length();
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "║\n";
    std::cout << "╚════════════════════════════════════════════╝" << RESET << "\n";
}

void UI::PrintBox(const std::string& content) {
    std::cout << BLUE << "┌────────────────────────────────────────────┐\n";
    std::cout << "│ " << RESET << content;
    
    // Add padding
    int padding = 42 - content.length();
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << BLUE << " │\n";
    std::cout << "└────────────────────────────────────────────┘" << RESET << "\n";
}

void UI::PrintSeparator() {
    std::cout << BLUE << "────────────────────────────────────────────" << RESET << "\n";
}

void UI::PrintCombatMessage(const std::string& message) {
    std::cout << RED << "⚔ " << message << RESET << std::endl;
}

void UI::PrintSuccessMessage(const std::string& message) {
    std::cout << GREEN << "✓ " << message << RESET << std::endl;
}

void UI::PrintErrorMessage(const std::string& message) {
    std::cout << RED << "✗ " << message << RESET << std::endl;
}