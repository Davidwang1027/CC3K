#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "celltype.h"
#include "state.h"

class Cell : public Subject<State>, public Observer<State>{
    std::size_t r, c;
    CellType type;
public:
    Cell(std::size_t r, std::size_t c, CellType type);
    Cell();
    void setCoords(std::size_t r, std::size_t c);
    void setType(CellType type);
    std::size_t getRow();
    std::size_t getCol();
    CellType getCellType();
    void notify(Subject& whoNotified) override;
};

#endif
