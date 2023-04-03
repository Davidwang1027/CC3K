#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

enum class Direction;
class Player : public Entity{
private:
    int gold;
public:
    Player(int hp = 0, int atk = 0, int def = 0, int gold = 0) : Entity{hp, atk, def}, gold{gold} {}
    void attack(Entity& whodefend);
    void move(Direction dir);
    virtual void setgold(int plusgold);
    int getGold();
};

#endif