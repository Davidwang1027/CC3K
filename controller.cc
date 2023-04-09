#include "controller.h"
#include <chrono>
#include <algorithm>
#include <random>

Position Controller::dirToPos(std::string direction){
    Position pos = dungeon.at(level)->getPlayerPos();
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
    } else if (race == "e") {
        player = new Elf();
    } else if (race == "d") {
        player = new Dwarf();
    } else if (race == "o") {
        player = new Orc();
    }
}

void Controller::playerMove(std::string direction){
    Position pos = dirToPos(direction);
    dungeon.at(level)->playerMove(pos);
    dungeon.at(level)->goldnavigation();
    dungeon.at(level)->suitnavigation();
    dungeon.at(level)->enemyAction();
    isLost = dungeon.at(level)->isLost();
    std::cout << *dungeon.at(level);
    if (dungeon.at(level)->isWon()){
        std::cout << "You win!" << std::endl;
    };
}

void Controller::useItem(std::string direction){
    Position pos = dirToPos(direction);
    dungeon.at(level)->playerUse(pos);
    dungeon.at(level)->enemyAction();
    isLost = dungeon.at(level)->isLost();
    std::cout << *(dungeon.at(level));
}

void Controller::playerAttack(std::string direction){
    Position pos = dirToPos(direction);
    dungeon.at(level)->playerAttack(pos);
    dungeon.at(level)->enemyAction();
    isLost = dungeon.at(level)->isLost();
    std::cout << *(dungeon.at(level));
}

void Controller::initMap(){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::vector<int> s = {1,2,3,4,5};
    std::shuffle(s.begin(), s.end(), rng);
    suitLevel = s.at(0);
    for (int i = 1; i < 6; i++) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        Floor *f = new Floor();
        f->init(player,i,suitLevel,rng);
        dungeon.emplace_back(f);
    }
}

void Controller::restart() {

    for (int i = 0; i < 5; i++) {
        delete dungeon.at(i);
        std::default_random_engine rng{seeds.at(i)};
        Floor *f = new Floor();
        f->init(player,i,suitLevel,rng);
        dungeon.emplace_back(f);
    }
}
