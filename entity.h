#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "position.h"


class Entity{
private:
    int hp, atk, def;
    std::vector<Position> availableDestination;
public:
    Entity(int hp, int atk, int def);
    std::vector<Position> getDestinations() const { return availableDestination; };
    void setDestination(std::vector<Position> newDest){ this->availableDestination = newDest; };
    //virtual void attack(Entity& whodefend) = 0;
    virtual int getHp(){ return hp; };
    virtual int getAtk(){ return atk; };
    virtual int getDef(){ return def; };
    virtual void setHp(int new_hp){ hp = new_hp; };
    virtual void setAtk(int new_atk){ atk = new_atk; };
    virtual void setDef(int new_def){ def = new_def; };
    
};

#endif
