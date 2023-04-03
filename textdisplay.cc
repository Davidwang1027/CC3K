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
    case CellType::passage:
        theDisplay[r][c] = '#';
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
    case CellType::suit:
        theDisplay[r][c] = 'S';
        break;
    case CellType::player:
        theDisplay[r][c] = '@';
        break;
    case CellType::vampire:
        theDisplay[r][c] = 'V';
        break;
    case CellType::troll:
        theDisplay[r][c] = 'T';
        break;
    case CellType::goblin:
        theDisplay[r][c] = 'N';
        break;
    case CellType::dragon:
        theDisplay[r][c] = 'D';
        break;
    case CellType::merchant:
        theDisplay[r][c] = 'M';
        break;
    case CellType::phoenix:
        theDisplay[r][c] = 'X';
        break;
    }
}

std::ostream& operator<<(std::ostream& out, const TextDisplay& td){
    for (auto row : td.theDisplay){
        for (auto col : row){
            switch (col){
            case '@':
                out << "\033[31m@\033[0m";
                break;
            case 'V':
                out << "\033[31;2mV\033[0m";
                break;
            case 'N':
                out << "\033[32mG\033[0m";
                break;
            case '\\':
                out << "\033[31m@\033[0m";
                break;
            case 'G':
                out << "\033[38;5;214mG\033[0m";
            default:
                out << col;
            }
            out << std::endl;
        }
        return out;
    }
}
