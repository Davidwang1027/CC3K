#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"

class Compass : public Item{
public:
    Compass() :Item{ false, "Compass" } {}
    void use(Player*& p){
        return;
    }
};

#endif
