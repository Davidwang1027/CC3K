#ifndef SUIT_H
#define SUIT_H
#include "item.h"
#include "decorator.h"
#include "Player.h"
#include "dragon.h"


class Player;
class Suit : public Item, public Decorator{
    bool isProtected = false;
    Dragon* dargon = nullptr;
public:
    Suit(Player *component) : Decorator(component) {}
    void setIsProtected(bool isProtected) {
        this->isProtected = isProtected;
    }
    void use(Player*& p) {

    }
    

};

#endif