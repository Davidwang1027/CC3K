#ifndef SUIT_H
#define SUIT_H
#include "item.h"
#include "Player.h"
#include "dragon.h"


class Player;
class Suit : public Item{
    bool isProtected = false;
    Dragon* dragon = nullptr;
public:
    void setIsProtected(bool isProtected){
        this->isProtected = isProtected;
    }
    void use(Player*& p){ p->setSuit(true); };
};

#endif
