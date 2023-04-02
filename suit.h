#include "item.h"
#include "decorator.h"

class Player;
class suit : public Item, public Decorator{
    public:
        Suit(Player *component);
}