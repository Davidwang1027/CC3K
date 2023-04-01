#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Cell : public Subject, public Observer{
    int r, c;
    char type;
public:
    Cell(int r, int c, char type);
    void setCoords(int r, int c);
    void setType(char type);
    int getRow();
    int getCol();
    char getType();
    void notify(Subject& whoNotified) override;
};

#endif
