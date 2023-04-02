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
    int getHp() { return hp; };
    int getAtk() { return atk; };
    int getDef() { return def; };
    void setHp(int new_hp) { hp = new_hp; };
    void setAtk(int new_atk) { atk = new_atk; };
    void setDef(int new_def) { def = new_def; };
};

#endif
