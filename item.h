#include "cell.h"
#include "player.h"
class Item{
public:
    virtual void use(Player& p) = 0;
};
