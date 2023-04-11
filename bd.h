#ifndef BD_H
#define BD_H
#include "tempotion.h"
#include "player.h"

class BD : public Tempotion{
public:
    BD(Player* component) : Tempotion{ component , "BD" }{}
    float getDef() override{ return component->getDef() + 5; }
    void use(Player*& p) override;
};

#endif
