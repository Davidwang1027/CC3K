#include "bd.h"

void BD::use(Player*& p){
    p = new BD{ p };
}
