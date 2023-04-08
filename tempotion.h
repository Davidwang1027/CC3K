#ifndef TEMPOTION_H
#define TEMPOTION_H
#include "item.h"
#include "decorator.h"
class Player;
class Tempotion : public Item, public Decorator{
public:
    Tempotion(Player* component) : Decorator{ component }{}
    virtual void use(Player*& p) override;
};


#endif
