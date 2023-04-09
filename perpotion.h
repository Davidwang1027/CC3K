#ifndef PERPOTION_H
#define PERPOTION_H
#include "item.h"
#include <string>
class Perpotion : public Item{
    int value;
public:
    Perpotion(int value) : value{ value }{};
    void use(Player*& p) override{}
};
#endif
