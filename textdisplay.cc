#include "textdisplay.h"
#include "subject.h"
#include "celltype.h"

void TextDisplay::notify(Subject<State>& whoNotified){
    State s = whoNotified.getState();
    CellType ct = s.type;
    size_t r = s.r;
    size_t c = s.c;
    bool isv = s.isStairVisible;
    switch (ct){
    case CellType::vWall:
        theDisplay[r][c] = '|';
        break;
    case CellType::hWall:
        theDisplay[r][c] = '-';
        break;
    case CellType::door:
        theDisplay[r][c] = '+';
        break;
    case CellType::tile:
        theDisplay[r][c] = '.';
        break;
    case CellType::stair:
        if (isv){
            theDisplay[r][c] = '\\';
        } else{
            theDisplay[r][c] = '.';
        }
        break;
    case CellType::empty:
        theDisplay[r][c] = ' ';
        break;
    case CellType::potion:
        theDisplay[r][c] = 'P';
        break;
    case CellType::gold:
        theDisplay[r][c] = 'G';
        break;
    case CellType::compass:
        theDisplay[r][c] = 'C';
        break;






    }
}

std::ostream& operator<<(std::ostream& out, const TextDisplay& td){
    for (auto row : td.theDisplay){
        for (auto col : row){
            if (col == '@'){
                out << ' ';
            } else
                out << col;
        }
        out << std::endl;
    }
    return out;
}
