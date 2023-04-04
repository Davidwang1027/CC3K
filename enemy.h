#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"

class Enemy : public Entity{
public:
    Enemy(int hp, int atk, int def) : Entity(hp, atk, def){};
    virtual void attack(Player& whodefend);
    virtual void dlcAttack(Entity& whodefend) = 0;
};

#endif
