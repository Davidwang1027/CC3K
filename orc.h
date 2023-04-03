#ifndef ORC_H
#define ORC_H

#include "player.h"

class Orc : public Player {
    public:
    Orc() : Player(180, 180, 30, 25, 0) {};
    void addGold(float new_gold) override { gold = new_gold / 2; }
};

#endif
