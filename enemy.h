#ifndef ENEMY
#define ENEMY

#include "entity.h"

class Enemy : public Entity{
public:
    void attack(Entity& whodefend) override;
    virtual void dlcAttack(Entity& whodefend) = 0;
    virtual void move() override;
    virtual void notify(Subject<State> &whoNotified);
};

#endif
