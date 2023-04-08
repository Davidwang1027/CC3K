#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"

class Compass : public Item{
    Enemy* e;
public:
    Compass(Enemy* e) :Item{ false, "Compass" }, e{ e }{}
    void use(Player*& p){
        return;
    }
};

#endif
