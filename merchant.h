#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy{
    bool hostile = false;
public:
    Merchant() : Enemy("Merchant", 30, 70, 5){};
    void setHostile(bool hostile){ this->hostile = hostile; }
    bool getHostile() const{ return hostile; }
    std::string attack(Player& p) override{
        if (hostile){
            return(this->attack(p));
        } else{
            return "";
        }
    };
};




#endif
