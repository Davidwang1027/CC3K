#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "floor.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include <vector>
class Controller{
    Player* player;
    std::vector<Floor*> dungeon;
    Position dirToPos(std::string direction);
    bool isLost = false;
    std::vector<unsigned int> seeds;
    int level;
    int suitLevel;
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
