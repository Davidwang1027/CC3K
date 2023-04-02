#include "textdisplay.h"
#include "celltype.h"
void TextDisplay::notify(Subject& whoNotified){
    CellType = whoNotified.getType(); // change function name
    switch (){

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
