#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
class Dragon : public Enemy{
    bool hostile = false;
public:
    Dragon() : Enemy(150, 20, 20){};
    void dlcAttack(Entity& whodefend) override;
};




#endif
