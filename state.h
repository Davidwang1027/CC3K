#ifndef STATE_H
#define STATE_H
#include "celltype.h"
#include "position.h"
class Enemy;
class Player;
class Item;
struct State{
    Position pos;
    CellType type;
    Player* player;
    Enemy* enemy;
    Item* item;
    bool stairVisible;
};

#endif
