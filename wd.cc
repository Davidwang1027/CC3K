#include "wd.h"
#include "bd.h"

void WD::use(Player*& p) {
    if (p->getName() == "Elf") {
        p = new BD{p};
    } else { 
        p = new WD{p};
    }
}
