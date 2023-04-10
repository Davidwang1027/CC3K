#ifndef TEMPOTION_H
#define TEMPOTION_H
#include "item.h"
#include "decorator.h"

class Tempotion : public Item, public Decorator{
public:
    Tempotion(Player* component) : Decorator{ component }{}
    virtual void use(Player*& p) override;
    void setHp(int hp) override{ component->setHp(hp); }
    std::string attack(Enemy& whodefend) override{ return component->attack(whodefend); }
    std::string addGold(float gold) override{ return (component->addGold(gold)); }
    virtual int getAtk() override{ return component->getAtk(); }
    virtual int getHp() override{ return component->getHp(); }
    virtual float getDef() override{ return component->getDef(); }
    virtual float getGold() override{ return component->getGold(); }
    virtual std::string getName() override{ return component->getName(); }
};


#endif 
