#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

class Cell : public Subject, public Observer{
    std::size_t r, c;
    char type;
public:
    Cell(std::size_t r, std::size_t c, char type);
    void setCoords(std::size_t r, std::size_t c);
    void setType(char type);
    std::size_t getRow();
    std::size_t getCol();
    char getType();
    void notify(Subject& whoNotified) override;
};

#endif
