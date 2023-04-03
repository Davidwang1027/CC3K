#include "player.h"

class Dwarf : public Player{
    public:
        void setGold(float new_gold) override { gold = new_gold * 2; }
};
