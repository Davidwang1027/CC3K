#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player{
public:
    Human() : Player("Human", 140, 140, 20, 20, 0){};
};

#endif
