#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Player;
class Enemy : public Entity{
    int ceiling(int num);
    bool hasCompass = false;
public:
    Enemy(std::string name, int hp, int atk, int def) : Entity(name, hp, atk, def){};
    virtual std::string attack(Player& whodefend);
    // virtual std::string dlcAttack(Player& whodefend) = 0;
    virtual void setHostile(bool hostile){};
    bool getCompass(){ return hasCompass; }
    void setCompass(){ hasCompass = true; }
};

#endif
