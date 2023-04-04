#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity{
public:
    Enemy(int hp, int atk, int def) : Entity(hp, atk, def){};
    void attack(Entity& whodefend) override;
    virtual void dlcAttack(Entity& whodefend) = 0;
};

#endif
