#ifndef BA_H
#define BA_H
#include "tempotion.h"
class BA : public Tempotion{
public:
    BA(Player* component) : Tempotion{ component , "BA" }{}
    int getAtk() override{ return component->getAtk() + 5; }
    int getHp() override{ return component->getHp(); }
    float getDef() override{ return component->getDef(); }
    std::string getName() override{ return component->getName(); }
    void use(Player*& p) override;

};

#endif
