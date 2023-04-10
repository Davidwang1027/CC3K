#ifndef DECORATOR_H
#define DECORATOR_H

#include "player.h"

class Decorator : public Player{
protected:
    Player* component;
public:
    Decorator(Player* component) : component{ component }{};
    virtual ~Decorator(){ delete component; };
    Player* getComp(){ return component; }
};

#endif
