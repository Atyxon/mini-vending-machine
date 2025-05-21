#ifndef ITEM_CLASS_H
#define ITEM_CLASS_H

#include <Arduino.h>

class Item {
public:
    int id;
    String name;
    float cost;

    // Constructor
    Item(int _id, String _name, float _cost) {
        id = _id;
        name = _name;
        cost = _cost;
    }
};

#endif