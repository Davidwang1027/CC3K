#include "floor.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "werewolf.h"
#include "phoenix.h"
#include "merchant.h"
#include "dragon.h"
#include "player.h"

int suitrandomGeneration(){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int itemnumberrandomGeneration(){
    std::vector<int> v = { 0, 1, 2 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int chamberrandomGeneration(){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

Position randomPosition(std::vector<Position> chamber){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(chamber.begin(), chamber.end(), rng);
    return *(chamber.begin());
}

std::vector<std::vector<Position>> Floor::chamberConstruction(){
    std::vector<Position> chamber1;
    std::vector<Position> chamber2;
    std::vector<Position> chamber3;
    std::vector<Position> chamber4;
    std::vector<Position> chamber5;
    // chamber 1
    for (size_t i = 2; i < 29; i++){
        for (size_t j = 3; j < 7; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber1.emplace_back(Position{ i, j });
            }
        }
    }
    // chamber 2
    for (size_t i = 39; i < 79; i++){
        for (size_t j = 3; j < 8; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber2.emplace_back(Position{ i, j });
            }
        }
        for (size_t i = 58; i < 79; i++){
            for (size_t j = 8; j < 14; j++){
                if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                    chamber2.emplace_back(Position{ i, j });
                }
            }
        }
    }

    // chamber 3
    for (size_t i = 38; i < 52; i++){
        for (size_t j = 10; j < 13; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber3.emplace_back(Position{ i, j });
            }
        }
    }
    // chamber 4
    for (size_t i = 3; i < 27; i++){
        for (size_t j = 15; j < 24; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber4.emplace_back(Position{ i, j });
            }
        }
    }
    // chamber 5
    for (size_t i = 37; i < 79; i++){
        for (size_t j = 16; j < 24; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber5.emplace_back(Position{ i, j });
            }
        }
    }
    return { chamber1, chamber2, chamber3, chamber4, chamber5 };
}
CellType enemyrandomGeneration(){
    std::vector<CellType> v = { CellType::vampire, CellType::vampire, CellType::vampire, CellType::werewolf,
    CellType::werewolf, CellType::werewolf, CellType::werewolf, CellType::goblin, CellType::goblin, CellType::goblin,
    CellType::goblin, CellType::goblin, CellType::troll, CellType::troll, CellType::phoenix, CellType::phoenix,
    CellType::merchant, CellType::merchant };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

CellType itemrandomGeneration(){
    std::vector<CellType> v = { CellType::potion, CellType::gold, CellType::gold, CellType::gold, CellType::gold };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

std::ostream& operator<<(std::ostream& out, const Floor& f){
    out << *(f.td);
    return out;
}

//
void mapGenerator(std::string filename, std::vector<std::vector<Cell>>& theFloor, TextDisplay* td){
    std::ifstream file {filename};
    std::string line;
    size_t row = 0;
    while (getline(file, line)){
        std::vector<Cell> temp;
        for (size_t i = 0; i < line.length(); i++){
            Cell cell;
            cell.attach(td);
            char c = line[i];
            if (c == '|'){
                cell.setType(CellType::vWall);
            } else if (c == '-'){
                cell.setType(CellType::hWall);
            } else if (c == '+'){
                cell.setType(CellType::door);
            } else if (c == '#'){
                cell.setType(CellType::passage);
            } else if (c == '.'){
                cell.setType(CellType::tile);
            } else if (c == ' '){
                cell.setType(CellType::empty);
            } else if (c == '\\'){
                cell.setType(CellType::stair);
            }
            cell.setPos({ row, i });
            temp.emplace_back(cell);
        }
        theFloor.emplace_back(temp);
        row++;
    }
}

void Floor::init(Player* player, int level){
    this->player = player;
    this->level = level;
    delete td;
    td = new TextDisplay(25, 79);
    mapGenerator("map.txt", theFloor, td);

    std::vector<std::vector<Position>> chambers = chamberConstruction();
    for (int i = 0; i < 20; i++){
        int chamberNum = chamberrandomGeneration();
        CellType enemy = enemyrandomGeneration();
        Position enemyPos = randomPosition(chambers.at(chamberNum));
        Enemy* e;
        if (enemy == CellType::vampire){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::vampire);
            e = new Vampire();
        } else if (enemy == CellType::werewolf){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::werewolf);
            e = new Werewolf();
        } else if (enemy == CellType::goblin){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::goblin);
            e = new Goblin();
        } else if (enemy == CellType::troll){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::troll);
            e = new Troll();
        } else if (enemy == CellType::phoenix){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::phoenix);
            e = new Phoenix();
        } else if (enemy == CellType::merchant){
            theFloor.at(enemyPos.x).at(enemyPos.y).setType(CellType::merchant);
            e = new Merchant();
        }
        enemies.emplace_back(e);
    }
}
