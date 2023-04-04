#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include "player.h"
#include "Dragon.h"
class Gold : public Item{
    float value;
    bool isProtected = false;
    Dragon* dragon = nullptr;
public:
    Gold(float value, bool isProtected, Dragon* dragon) : value{ value }, isProtected{ isProtected }, dragon{ dragon }{}
    void use(Player& p) override;
    // no need for setDragon method because dragon is set in the constructor
    Dragon* getDragon(){
        return dragon;
    }
    // no need for setValue method because value is set in the constructor
    float getValue(){
        return value;
    }

    void setIsProtected(bool isProtected){
        this->isProtected = isProtected;
    }
    bool getIsProtected(){
        return isProtected;
    }






};

#endif
