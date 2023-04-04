#include "ba.h"

void BA::use(Player*& p){
    p = new BA{ p };
}
