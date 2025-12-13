#ifndef UI_H
#define UI_H

#include <string>

class UI {
public:
    // Colors
    static const std::string RESET;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string CYAN;
    static const std::string MAGENTA;
    static const std::string BOLD;
    
    // Screen control
    static void ClearScreen();
    static void PrintHeader(const std::string& title);
    static void PrintBox(const std::string& content);
    static void PrintSeparator();
    static void PrintCombatMessage(const std::string& message);
    static void PrintSuccessMessage(const std::string& message);
    static void PrintErrorMessage(const std::string& message);
};

#endif