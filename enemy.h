#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity{
public:
    void attack(Entity& whodefend) override;
    virtual void dlcAttack(Entity& whodefend) = 0;
    virtual void notify(Subject<State>& whoNotified);
};

#endif
