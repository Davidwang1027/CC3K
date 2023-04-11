#ifndef TEMPOTION_H
#define TEMPOTION_H
#include "item.h"
#include "decorator.h"

class Tempotion : public Item, public Decorator{
    std::string name;
public:
    Tempotion(Player* component, const std::string& name) : Item{ false }, Decorator{ component }, name{ name }{}
    virtual void use(Player*& p) override;
    void setHp(int hp) override{ component->setHp(hp); }
    std::string attack(Enemy& whodefend) override{ return component->attack(whodefend); }
    std::string addGold(float gold) override{ return (component->addGold(gold)); }
    int getMaxhp() override{ return component->getMaxhp(); }
    virtual int getAtk() override{ return component->getAtk(); }
    virtual int getHp() override{ return component->getHp(); }
    virtual float getDef() override{ return component->getDef(); }
    virtual float getGold() override{ return component->getGold(); }
    std::string getName() override{ return component->getName(); }
    std::string getPotionName(){ return name; }
    ~Tempotion(){};
};


#endif 
