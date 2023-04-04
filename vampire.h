#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "enemy.h"
class Vampire : public Enemy{
    void dlcAttack(Player& whodefend) override;
};

#endif
