#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemy.h"

class Goblin : public Enemy{
public:
    goblin() : Enemy("Goblin", 70, 5, 10) {}
    // std::string dlcAttack(Player& whodefend) override;
} 

#endif