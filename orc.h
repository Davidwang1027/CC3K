#ifndef ORC_H
#define ORC_H

#include "player.h"

class Orc : public Player{
public:
    Orc() : Player("Orc", 18000, 18000, 3000, 2500, 0){};
    std::string addGold(float new_gold) override{
        gold += new_gold / 2;
        return std::to_string(gold);
    }
};

#endif
