#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

#include <string>
class Enemy;
class Player : public Entity{
private:
    int maxhp;
    bool hasSuit;
protected:
    float gold;
public:
    Player(std::string name = "", int maxhp = 0, int hp = 0, int atk = 0, float def = 0, float gold = 0, bool hasSuit = false) : Entity{ name, hp, atk, def }, maxhp{ maxhp }, hasSuit{ hasSuit }, gold{ gold }{}
    virtual std::string attack(Enemy& whodefend);
    virtual std::string addGold(float plusgold);

    virtual void setGold(float newgold){ gold = newgold; }
    virtual float getGold();
    virtual int getMaxhp(){ return maxhp; }
    bool getSuit(){ return hasSuit; }
    void setSuit(bool suit){ hasSuit = suit; }
};

#endif
