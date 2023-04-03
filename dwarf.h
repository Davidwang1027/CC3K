#include "player.h"

class Dwarf : public Player{
    public:
        Dwarf() : Player(100, 100, 20, 30, 0) {};
        void setGold(float new_gold) override { gold = new_gold * 2; }
};
