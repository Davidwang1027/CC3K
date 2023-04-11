#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "position.h"
#include <string>

class Entity{
private:
    std::string name;
    int hp, atk;
    float def;
    std::vector<Position> availableDestination;
    bool isDead = false;
public:
    Entity(std::string name, int hp, int atk, float def) : name{ name }, hp{ hp }, atk{ atk }, def{ def }{};
    virtual std::string getName(){ return name; };
    std::vector<Position> getDestinations() const{ return availableDestination; };
    void addDestination(Position newDest){ availableDestination.emplace_back(newDest); };
    void clearDestinations(){ availableDestination.clear(); };
    virtual int getHp(){ return hp; };
    virtual int getAtk(){ return atk; };
    virtual float getDef(){ return def; };
    virtual void setHp(int new_hp){ hp = new_hp; };
    virtual void setAtk(int new_atk){ atk = new_atk; };
    virtual void setDef(float new_def){ def = new_def; };
    bool getDead(){ return isDead; };
    void setDead(){ isDead = true; };
};

#endif
