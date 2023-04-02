#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity{
public:
    Player(int hp = 0, int atk = 0, int def = 0) : Entity{hp, atk, def} {}
    void buff();
};

#endif