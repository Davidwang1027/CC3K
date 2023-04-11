#ifndef PERPOTION_H
#define PERPOTION_H
#include "item.h"
#include <string>
class Perpotion : public Item{
    int value;
public:
    Perpotion(int value, const std::string& name) : Item{ false, name }, value{ value }{};
    void use(Player*& p) override;
};
#endif
