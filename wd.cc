#include "wd.h"

void WD::use(Player*& p) {
    p = new WD{p};
}
