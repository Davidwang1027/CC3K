#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Cell : public Subject, public Observer{
    size_t r, c;
    char type;
public:
    Cell(size_t r, size_t c, char type);
    void setCoords(size_t r, size_t c);
    void setType(char type);
    size_t getRow();
    size_t getCol();
    char getType();
    void notify(Subject& whoNotified) override;
};

#endif
