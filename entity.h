#ifndef ENTITY_H
#define ENTITY_H

#include "cell.h"

class Entity : public Cell{
private:
    int hp, atk, def;
public:
    Entity(int hp, int atk, int def): atk{atk}, hp{hp}, def{def} {}
    virtual void attack() = 0;
    virtual void move() = 0;
    virtual int getHp() { return hp; };
    virtual int getAtk() { return atk; };
    virtual int getDef() { return def; };
    virtual void setHp(int new_hp) { hp = new_hp; };
    virtual void setAtk(int new_atk) { atk = new_atk; };
    virtual void setDef(int new_def) { def = new_def; };
};

#endif