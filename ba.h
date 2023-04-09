#ifndef BA_H
#define BA_H
#include "tempotion.h"
class BA : public Tempotion{
public:
    BA(Player* component) : Tempotion{ component }{}
    int getAtk() override{ return component->getAtk() + 5; }
    void use(Player*& p) override;
};

#endif
