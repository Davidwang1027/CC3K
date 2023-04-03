#include "tempotion.h"
#include "player.h"

class BD : public Tempotion {
    public:
        BD(Player *component) : Tempotion{component} {}
        int getDef() override { return component->getDef() + 5; }
};
