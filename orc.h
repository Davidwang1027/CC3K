#ifndef ORC_H
#define ORC_H

#include "player.h"

class Orc : public Player {
    public:
    void setGold(float new_gold) override { gold = new_gold / 2; }
};

#endif
