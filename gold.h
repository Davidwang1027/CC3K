#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include "player.h"
#include "dragon.h"
#include <string>

class Gold : public Item{
    float value;
public:
    Gold(float value, bool isProtected) : Item(isProtected, "Gold"), value{ value }{}
    void use(Player*& p) override;
    // no need for setDragon method because dragon is set in the constructor
    // no need for setValue method because value is set in the constructor
    std::string getValue();
};

#endif
