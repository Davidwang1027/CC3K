#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(int r, int c, char type) : r{ r }, c{ c }, type{ type }{}

void Cell::setCoords(int r, int c){
    this->r = r;
    this->c = c;
}

void Cell::setType(char type){
    this->type = type;
}

int Cell::getRow(){
    return r;
}

int Cell::getCol(){
    return c;
}

char Cell::getType(){
    return type;
}

void Cell::notify(Subject& whoNotified){
    // TODO
}
