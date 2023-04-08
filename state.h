#ifndef STATE_H
#define STATE_H
#include "celltype.h"
#include "position.h"
#include <string>
#include <vector>

struct State{
    Position pos;
    CellType type;
    std::string action;
};

#endif
