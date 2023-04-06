#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Player;
class Enemy : public Entity{
public:
    Enemy(std::string name, int hp, int atk, int def) : Entity(name, hp, atk, def){};
    virtual std::string attack(Player& whodefend);
    // virtual std::string dlcAttack(Player& whodefend) = 0;
};

#endif
