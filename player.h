#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

enum class Direction;
class Player : public Entity{
protected:
    float gold;
public:
    Player(int hp = 0, int atk = 0, int def = 0, int gold = 0) : Entity{hp, atk, def}, gold{gold} {}
    void attack(Entity& whodefend) override;
    void move(Direction dir);
    virtual void setGold(float plusgold);
    int getGold();
};

#endif
