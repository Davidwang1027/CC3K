#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity{
private:
    int maxhp;
protected:
    float gold;
public:
    Player(int maxhp = 0, int hp = 0, int atk = 0, int def = 0, float gold = 0) : Entity{ hp, atk, def }, maxhp{ maxhp }, gold{ gold }{}
    void attack(Entity& whodefend) override;
    virtual void addGold(float plusgold);
    float getGold();
};

#endif
