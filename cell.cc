#include "cell.h"
#include "subject.h"
#include "observer.h"

Cell::Cell(std::size_t r, std::size_t c, CellType type, bool isStairVisible) : r{ r }, c{ c }, type{ type }, isStairVisible{ isStairVisible }{
    this->setState(State{ r, c, type, isStairVisible });
}


void Cell::setCoords(std::size_t r, std::size_t c){
    this->r = r;
    this->c = c;
}

void Cell::setType(CellType type){
    this->type = type;
}

void Cell::setStair(bool isStairVisible){
    this->isStairVisible = isStairVisible;
}

std::size_t Cell::getRow(){
    return r;
}

std::size_t Cell::getCol(){
    return c;
}

bool Cell::getStair(){
    return isStairVisible;
}

CellType Cell::getCellType(){
    return type;
}

void Cell::notify(Subject& whoNotified){
    // TODO
}
