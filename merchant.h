#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy{
public:
    Merchant() : Enemy("Merchant", 30, 70, 5, false){};
};




#endif
