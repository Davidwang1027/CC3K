#include "item.h"
#include "decorator.h"

class player;
class suit : public Item, public Decorator{
    public:
        Suit(player *component);
}