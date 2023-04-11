#ifndef WA_H
#define WA_H

#include "tempotion.h"
#include "player.h"
class WA : public Tempotion{
public:
    WA(Player* component) : Tempotion{ component , "WA" }{}
    int getAtk() override{ return component->getAtk() - 5; }
    void use(Player*& p) override;
};

#endif
