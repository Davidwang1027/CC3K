#include "ba.h"

void BA::use(Player& p){
    p = BA(&p);
}
