#include "gold.h"

void Gold::use(Player*& p){
    if (!isProtected){
        p->addGold(value);
    }
    // try - catch? 
}
