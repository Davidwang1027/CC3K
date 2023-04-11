#include "wa.h"
#include "ba.h"

void WA::use(Player*& p){
    if (p->getName() == "Elf"){
        p = new BA{ p };
    } else{
        p = new WA{ p };
    }
}
