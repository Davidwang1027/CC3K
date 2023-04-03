#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "enemy.h"
class Vampire : public Enemy {
    void attack(Entity& whodefend) override;
};

#endif
