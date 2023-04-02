#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"

enum class CellType{
    vWall, hWall, passage, door, tile, stair, empty,  // map objects
    potion, gold, compass, suit, // item
    human, elf, dwarf, orc, // players
    vampire, troll, goblin, dragon, merchant, phoenix// enemies
};

class Cell : public Subject, public Observer{
    std::size_t r, c;
    CellType type;
public:
    Cell(std::size_t r, std::size_t c, CellType type);
    void setCoords(std::size_t r, std::size_t c);
    void setType(CellType type);
    std::size_t getRow();
    std::size_t getCol();
    CellType getType();
    void notify(Subject& whoNotified) override;
};

#endif
