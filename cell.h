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
