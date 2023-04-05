#ifndef PHOENIX_H
#define PHOENIX_H

#include "enemy.h"
class Phoenix : public Enemy{
public:
    Phoenix() : Enemy("Phoenix", 50, 35, 20){};
    std::string dlcAttack(Player& whodefend) override;
};

#endif
