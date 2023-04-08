#ifndef SUIT_H
#define SUIT_H
#include "item.h"
#include "player.h"
#include "dragon.h"


class Player;
class Suit : public Item{
public:
    Suit(bool isProtected) : Item(isProtected, "Suit"){}
    void use(Player*& p){ p->setSuit(true); };
};

#endif
