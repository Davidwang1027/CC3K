#ifdef PERPOTION_H
#define PERPOTION_H
#include "item.h"
#include <string>
class Perpotion : public Item {
    int value;
    public:
    Perpotion(int value) : hpChange{value} {}
}
#endif
