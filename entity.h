#ifndef ENTITY_H
#define ENTITY_H
#include "cell.h"

class entity : public cell{
private:
    int hp, atk, def;
public:
    void attack() = 0;
    void move() = 0;
}

#endif
