#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "enemy.h"
class Player : public Entity{
private:
    int maxhp;
    bool Suit;
protected:
    float gold;
public:
    Player(int maxhp = 0, int hp = 0, int atk = 0, int def = 0, float gold = 0, bool Suit = false) : Entity{ hp, atk, def }, maxhp{ maxhp }, gold{ gold }, Suit{Suit} {}
    virtual void attack(Enemy& whodefend);
    virtual void addGold(float plusgold);
    float getGold();
    bool hasSuit() {return Suit;}
};

#endif
