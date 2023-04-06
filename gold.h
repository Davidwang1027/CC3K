#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include "player.h"
#include "dragon.h"
class Gold : public Item{
    float value;
    Dragon* dragon = nullptr;
public:
    Gold(float value, bool isProtected, Dragon* dragon) : Item(isProtected, "Gold"), value{ value }, dragon{ dragon }{}
    void use(Player*& p) override;
    // no need for setDragon method because dragon is set in the constructor
    Dragon* getDragon(){
        return dragon;
    }
    // no need for setValue method because value is set in the constructor
    float getValue(){
        return value;
    }
};

#endif
