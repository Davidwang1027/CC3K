#include "perpotion.h"

void Perpotion::use(Player*& p){
    if (p->getName() == "Elf"){
        p->setHp(p->getHp() + 10);
    } else{
        p->setHp(p->getHp() + value);
    }

    if (p->getHp() > p->getMaxhp()){
        p->setHp(p->getMaxhp());
    }
}
