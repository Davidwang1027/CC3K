#ifndef STATE_H
#define STATE_H
#include "celltype.h"
#include "position.h"
#include <string>
#include <vector>

struct State{
    CellType type;
    std::vector<std::string> display; 
};

#endif
