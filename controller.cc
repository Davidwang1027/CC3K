#include "controller.h"
#include <chrono>
#include <algorithm>
#include <random>



Position Controller::dirToPos(std::string direction){
    Position pos = dungeon.at(level)->getPlayerPos();
    if (direction == "no"){
        pos.x--;
    } else if (direction == "so"){
        pos.x++;
    } else if (direction == "ea"){
        pos.y++;
    } else if (direction == "we"){
        pos.y--;
    } else if (direction == "ne"){
        pos.y++;
        pos.x--;
    } else if (direction == "nw"){
        pos.y--;
        pos.x--;
    } else if (direction == "se"){
        pos.y++;
        pos.x++;
    } else if (direction == "sw"){
        pos.y--;
        pos.x++;
    }
    return pos;
}


void Controller::setPlayer(std::string race){
    if (race == "h"){
        player = new Human();
    } else if (race == "e"){
        player = new Elf();
    } else if (race == "d"){
        player = new Dwarf();
    } else if (race == "o"){
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
        isWon = true;
        std::cout << "You win!" << std::endl;
        if (player->getName() == "Human"){
            std::cout << "Your score is " << (player->getGold() * 1.5) << std::endl;
        } else{
            std::cout << "Your score is " << player->getGold() << std::endl;
        }
    } else if (dungeon.at(level)->isOnStair()){
        level++;
        std::cout << "Welcome to level " << level + 1 << std::endl;
        std::cout << *(dungeon.at(level));
        while (static_cast<Decorator*>(player)->getComp() != nullptr){
            player = static_cast<Decorator*>(player)->getComp();
        }
    }
}

void Controller::useItem(std::string direction){
    Position pos = dirToPos(direction);
    usedTemp = dungeon.at(level)->playerUse(pos);
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

void Controller::initMap(std::string race){
    setPlayer(race);
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::vector<int> s = { 1,2,3,4,5 };
    std::shuffle(s.begin(), s.end(), rng);
    suitLevel = s.at(0);
    for (int i = 1; i < 6; i++){
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        seeds.emplace_back(seed);
        Floor* f = new Floor();
        f->init(player, i, suitLevel, rng);
        dungeon.emplace_back(f);
    }
    std::cout << *(dungeon.at(level));
}

void Controller::initMap(std::string race, std::string filename){
    setPlayer(race);
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::vector<int> s = { 1,2,3,4,5 };
    std::shuffle(s.begin(), s.end(), rng);
    suitLevel = s.at(0);
    for (int i = 1; i < 6; i++){
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        seeds.emplace_back(seed);
        Floor* f = new Floor();
        f->init(player, i, suitLevel, rng, filename);
        dungeon.emplace_back(f);
    }
    std::cout << *(dungeon.at(level));
}

void Controller::restart(std::string race){
    delete player;
    setPlayer(race);
    dungeon.clear();
    level = 0;
    for (int i = 1; i < 6; i++){
        std::default_random_engine rng{seeds.at(i - 1)};
        Floor* f = new Floor();
        f->init(player, i, suitLevel, rng);
        dungeon.emplace_back(f);
    }
    std::cout << *(dungeon.at(level));
}

void Controller::restart(std::string race, std::string filename){
    delete player;
    setPlayer(race);
    dungeon.clear();
    level = 0;
    for (int i = 1; i < 6; i++){
        std::default_random_engine rng{seeds.at(i - 1)};
        Floor* f = new Floor();
        f->init(player, i, suitLevel, rng, filename);
        dungeon.emplace_back(f);
    }
    std::cout << *(dungeon.at(level));
}
