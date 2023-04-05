#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "enemy.h"
class Vampire : public Enemy{
public:
    Vampire() : Enemy("Vampire", 50, 25, 25){};
};

#endif
