#ifndef SUIT_H
#define SUIT_H
#include "item.h"
#include "player.h"
#include "dragon.h"


class Player;
class Suit : public Item{
    Dragon* dragon = nullptr;
public:
    Suit(bool isProtected, Dragon* dragon) : Item(isProtected, "Suit"), dragon{ dragon }{}
    void use(Player*& p){ p->setSuit(true); };
    Dragon* getDragon(){
        return dragon;
    }
};

#endif
