#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(std::size_t r, std::size_t c, char type) : r{ r }, c{ c }, type{ type }{}

void Cell::setCoords(std::size_t r, std::size_t c){
    this->r = r;
    this->c = c;
}

void Cell::setType(char type){
    this->type = type;
}

std::size_t Cell::getRow(){
    return r;
}

std::size_t Cell::getCol(){
    return c;
}

char Cell::getType(){
    return type;
}

void Cell::notify(Subject& whoNotified){
    // TODO
}
