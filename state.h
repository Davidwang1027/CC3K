#ifndef STATE_H
#define STATE_H
#include "celltype.h"
#include "position.h"
#include <string>
#include <vector>
class Enemy;
class Player;
class Gold;
class Suit;
class Perpotion;
class Tempotion;

struct State{
    Position pos;
    CellType type;
    Player* player;
    Enemy* enemy;
    Gold* gold;
    Suit* suit;
    Tempotion* tempotion;
    Perpotion* perpotion;
    bool stairVisible;
    std::vector<std::string> display;
};

#endif
