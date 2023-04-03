#include "item.h"
#include "decorator.h"
class Player;
class Tempotion : public Item, public Decorator {
    public:
        Tempotion(Player *component): Decorator{component} {}
};
