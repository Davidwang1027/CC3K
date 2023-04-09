#ifndef WEREWOLF_H
#define WEREWOLF_H
#include "enemy.h"
class Werewolf : public Enemy{
public:
    Werewolf() : Enemy("Werewolf", 120, 30, 5){};
    // std::string dlcAttack(Player& whodefend) override;
};

#endif
