#include "player.h"

class Orc : public Player {
    public:
    Orc() : Player(180, 180, 30, 25, 0) {};
    void setGold(float new_gold) override { gold = new_gold / 2; }
};
