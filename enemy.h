#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"
#include <string>

class Enemy : public Entity{
public:
    Enemy(int hp, int atk, int def) : Entity(hp, atk, def){};
    virtual std::string attack(Player& whodefend);
    virtual std::string dlcAttack(Player& whodefend) = 0;
};

#endif
