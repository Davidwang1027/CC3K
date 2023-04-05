#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
class Dragon : public Enemy{
    bool hostile = false;
public:
    Dragon() : Enemy("Dragon", 150, 20, 20){};
    std::string dlcAttack(Player& whodefend) override;
};




#endif
