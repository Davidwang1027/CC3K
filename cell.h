#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Cell : public Subject, public Observer{
    std::size_t r, c;
    char type;
public:
    Cell(std::size_t r, std::size_t c, char type);
    void setCoords(int r, int c);
    void setType(char type);
    int getRow();
    int getCol();
    char getType();
    void notify(Subject& whoNotified) override;
};

#endif
