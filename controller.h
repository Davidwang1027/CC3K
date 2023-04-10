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
    int level = 0;
    int suitLevel;
    bool usedTemp;
    bool isWon = false;
public:
    Controller() = default;
    void setPlayer(std::string race);
    void playerMove(std::string direction);
    void useItem(std::string direction);
    void playerAttack(std::string direction);
    void initMap(std::string race);
    void initMap(std::string race, std::string filename);
    void restart(std::string race);
    void restart(std::string race, std::string filename);
    void quit();
    bool getIsLost(){ return isLost; }
    bool getIsWon(){ return isWon; }
};

#endif
