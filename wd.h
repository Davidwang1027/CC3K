#include "tempotion.h"
#include "player.h"

class WD : public Tempotion {
    public:
        WD(Player *component) : Tempotion{component} {}
        int getDef() override { return component->getDef() - 5; }
};
