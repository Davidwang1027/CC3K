#include "tempotion.h"
#include "player.h"
class WA : public Tempotion {
    public:
        WA(Player *component): Tempotion{component} {}
        int getAtk() override { return component->getAtk() - 5; }
};