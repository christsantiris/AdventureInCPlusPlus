#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    int id;
    std::string name;
    int price;
    
    Item(int itemId, std::string itemName, int itemPrice);
};

#endif