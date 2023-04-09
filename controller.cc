#include "controller.h"

Position Controller::dirToPos(std::string direction){
    Position pos = floor->getPlayerPos();
    if (direction == "no"){
        pos.y--;
    } else if (direction == "so"){
        pos.y++;
    } else if (direction == "ea"){
        pos.x++;
    } else if (direction == "we"){
        pos.x--;
    } else if (direction == "ne"){
        pos.x++;
        pos.y--;
    } else if (direction == "nw"){
        pos.x--;
        pos.y--;
    } else if (direction == "se"){
        pos.x++;
        pos.y++;
    } else if (direction == "sw"){
        pos.x--;
        pos.y++;
    }
    return pos;
}


void Controller::setPlayer(std::string race){
    if (race == "h"){
        player = new Human();
    }
}

void Controller::playerMove(std::string direction){
    Position pos = dirToPos(direction);
    floor->playerMove(pos);
    floor->goldnavigation();
    floor->suitnavigation();
    floor->enemyAction();
    isLost = floor->isLost();
    std::cout << *floor;
    if (floor->isWon()){
        std::cout << "You win!" << std::endl;
    };
}

void Controller::useItem(std::string direction){
    Position pos = dirToPos(direction);
    floor->playerUse(pos);
    floor->enemyAction();
    isLost = floor->isLost();
    std::cout << *floor;
}

void Controller::playerAttack(std::string direction){
    Position pos = dirToPos(direction);
    floor->playerAttack(pos);
    floor->enemyAction();
    isLost = floor->isLost();
    std::cout << *floor;
}

void Controller::initMap(){
    
}
