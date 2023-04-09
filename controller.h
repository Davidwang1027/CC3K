#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "floor.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
class Controller{
    Player* player;
    Floor* floor;
    Position dirToPos(std::string direction);
    bool isLost = false;
public:
    Controller();
    void setPlayer(std::string race);
    void playerMove(std::string direction);
    void useItem(std::string direction);
    void playerAttack(std::string direction);
    void initMap();
    void restart();
    void quit();
    void displayAction();
    bool getIsLost(){ return isLost; }
};

#endif
