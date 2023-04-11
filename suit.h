#ifndef SUIT_H
#define SUIT_H
#include "item.h"
#include "player.h"
#include "dragon.h"
#include "position.h"

class Player;
class Suit : public Item{
    Position dp;
public:
    Suit(bool isProtected, Position dp) : Item(isProtected, "Suit"), dp{ dp } {}
    Position getdp() { return dp; }
    void setdp(Position dp) { this->dp = dp; }
    void use(Player*& p){ p->setSuit(true); };
};

#endif
