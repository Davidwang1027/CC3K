#include "textdisplay.h"

void TextDisplay::notify(Subject& whoNotified){

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
