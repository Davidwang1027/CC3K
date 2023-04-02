#ifndef ENTITY_H
#define ENTITY_H

#include "cell.h"

class Entity : public Cell{
private:
    int hp, atk, def;
public:

    virtual void attack() = 0;
    virtual void move() = 0;
};

#endif
