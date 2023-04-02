#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(size_t r, size_t c, char type) : r{ r }, c{ c }, type{ type }{}

void Cell::setCoords(size_t r, size_t c){
    this->r = r;
    this->c = c;
}

void Cell::setType(char type){
    this->type = type;
}

size_t Cell::getRow(){
    return r;
}

size_t Cell::getCol(){
    return c;
}

char Cell::getType(){
    return type;
}

void Cell::notify(Subject& whoNotified){
    // TODO
}
