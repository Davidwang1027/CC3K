#ifndef PHOENIX_H
#define PHOENIX_H

#include "enemy.h"
class Phoenix : public Enemy{
public:
    Phoenix() : Enemy(50, 35, 20){};
    void dlcAttack(Entity& whodefend) override;
};

#endif
