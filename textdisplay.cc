#include "textdisplay.h"
#include "state.h"
void TextDisplay::notify(Subject<State>& whoNotified){
    CellType = whoNotified.getState(); // change function name

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
