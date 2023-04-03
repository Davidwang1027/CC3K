#include "textdisplay.h"
#include "subject.h"
#include "celltype.h"

void TextDisplay::notify(Subject<State>& whoNotified){
    State s = whoNotified.getState();
    CellType t = s.type;
    size_t r = s.r;
    size_t c = s.c;
    switch (t){
    case CellType::vWall:
        theDisplay[r][c] = '|';
        break;
    case CellType::hWall:
        theDisplay[r][c] = '-';
    }

}

std::ostream& operator<<(std::ostream& out, const TextDisplay& td){
    for (auto row : td.theDisplay){
        for (auto col : row){
            out << col;
        }
        out << std::endl;
    }
    return out;
}
