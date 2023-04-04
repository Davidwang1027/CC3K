#ifndef STATE_H
#define STATE_H
#include "celltype.h"
class Entity;
class Item;
struct State{
    size_t r, c;
    CellType type;
    Entity* entity;
    Item* item;
    bool stairVisible;
};

#endif
