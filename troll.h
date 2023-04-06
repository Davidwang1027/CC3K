#ifndef TROLL_H
#define TROLL_H
#include "enemy.h"
class Troll : public Enemy{
public:
    Troll() : Enemy("Troll", 120, 25, 15){};
    //std::string dlcAttack(Player& whodefend) override;
};

#endif
