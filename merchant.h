#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy{
    bool hostile = false;
public:
    Merchant() : Enemy(30, 70, 5){};
    void setHostile(bool hostile){ this->hostile = hostile; }
    bool getHostile() const{ return hostile; }
    void attack(Player& p) override{
        if (hostile){
            this->attack(p);
        }
    };
};




#endif
