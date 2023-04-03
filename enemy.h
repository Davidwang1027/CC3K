#ifndef ENEMY
#define ENEMY

#include "entity.h"

class Enemy : public Entity{
public:
    virtual void attack(Entity& whodefend) override;
    virtual void dlcAttack(Entity& whodefend) = 0;
    virtual void move() override;
};

#endif
