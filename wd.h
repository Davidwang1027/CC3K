#ifndef WD_H
#define WD_H

#include "tempotion.h"
#include "player.h"

class WD : public Tempotion {
    public:
        WD(Player *component) : Tempotion{component} {}
        int getDef() override { return component->getDef() - 5; }
        void use(Player* p) override;
};

#endif
