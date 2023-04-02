#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(std::size_t r, std::size_t c, CellType type) : r{ r }, c{ c }, type{ type }{}

void Cell::setCoords(std::size_t r, std::size_t c){
    this->r = r;
    this->c = c;
}

void Cell::setType(CellType type){
    this->type = type;
}

std::size_t Cell::getRow(){
    return r;
}

std::size_t Cell::getCol(){
    return c;
}

CellType Cell::getType(){
    return type;
}

void Cell::notify(Subject& whoNotified){
    // TODO
}
