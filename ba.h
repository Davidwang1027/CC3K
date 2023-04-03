#include "tempotion.h"
#include "player.h"
class BA : public Tempotion {
    public:
        BA(Player *component): Tempotion{component} {}
        int getAtk() override { return component->getAtk() + 5; }
};
