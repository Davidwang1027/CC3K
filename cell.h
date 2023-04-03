#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "celltype.h"
#include "state.h"

class Cell : public Subject<State>, public Observer<State>{
    std::size_t r, c;
    CellType type;
    bool isStairVisible = false;
public:
    Cell(std::size_t r, std::size_t c, CellType type, bool isStairVisible);
    Cell();
    void setCoords(std::size_t r, std::size_t c);
    void setType(CellType type);
    void setStair(bool isStairVisible);
    std::size_t getRow();
    std::size_t getCol();
    CellType getCellType();
    bool getStair();
    void notify(Subject<State>& whoNotified) override;
};

#endif
