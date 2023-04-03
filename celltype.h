#ifndef CELLTYPE_H
#define CELLTYPE_H
enum class CellType{
    vWall, hWall, passage, door, tile, stair, empty,  // map objects
    potion, gold, compass, suit, // item
    player, // players
    vampire, troll, goblin, dragon, merchant, phoenix // enemies
};


#endif
