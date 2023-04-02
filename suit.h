#include "item.h"
#include "decorator.h"

class Player;
class Suit : public Item, public Decorator{
    public:
        Suit(Player *component);
};