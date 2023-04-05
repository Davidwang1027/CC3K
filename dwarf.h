#ifndef DWARF_H
#define DWARF_H

#include "player.h"

class Dwarf : public Player{
public:
    Dwarf() : Player("Dwarf", 100, 100, 20, 30, 0){};
    std::string addGold(float new_gold) override{
        gold += new_gold * 2;
        return std::to_string(gold);
    }
};

#endif
