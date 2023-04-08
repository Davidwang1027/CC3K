#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "floor.h"

class Controller{
    Player* player;
    Floor* floor;
public:
    Controller(Player* player, Floor* floor) : player{ player }{}
    void movePlayer(std::string direction);
    void useItem(std::string direction);
    void attack(std::string direction);
    void initMap();
    void restart();
    void quit();


};

#endif
