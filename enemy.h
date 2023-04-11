#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Player;
class Enemy : public Entity{
    bool ishostile = true;
    bool hasCompass = false;
public:
    Enemy(std::string name, int hp, int atk, float def, bool ishostile = true) : Entity(name, hp, atk, def), ishostile{ ishostile }{};
    virtual std::string attack(Player& whodefend);
    // virtual std::string dlcAttack(Player& whodefend) = 0;
    void setHostile(bool hostile){ ishostile = hostile; };
    bool getHostile(){ return ishostile; }
    bool getCompass(){ return hasCompass; }
    void setCompass(){ hasCompass = true; }
};

#endif
