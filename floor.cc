#include "floor.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include "vampire.h"
#include "decorator.h"
#include "goblin.h"
#include "troll.h"
#include "werewolf.h"
#include "phoenix.h"
#include "merchant.h"
#include "dragon.h"
#include "player.h"
#include "tempotion.h"
#include "ba.h"
#include "bd.h"
#include "wa.h"
#include "wd.h"
#include "gold.h"


void erase(std::vector<Position>& v, Position p){
    for (size_t i = 0; i < v.size(); i++){
        if (v.at(i).r == p.r && v.at(i).c == p.c){
            v.erase(v.begin() + i);
        }
    }
}
int suitRandomGeneration(){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int itemNumberRandomGeneration(){
    std::vector<int> v = { 0, 1, 2 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int chamberRandomGeneration(){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

Position randomPosition(std::vector<Position>& chamber){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(chamber.begin(), chamber.end(), rng);
    Position p = *(chamber.begin());
    chamber.erase(chamber.begin());
    return p;
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
CellType enemyRandomGeneration(){
    std::vector<CellType> v = { CellType::vampire, CellType::vampire, CellType::vampire, CellType::werewolf,
    CellType::werewolf, CellType::werewolf, CellType::werewolf, CellType::goblin, CellType::goblin, CellType::goblin,
    CellType::goblin, CellType::goblin, CellType::troll, CellType::troll, CellType::phoenix, CellType::phoenix,
    CellType::merchant, CellType::merchant };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());

}

CellType itemRandomGeneration(){
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

int randomGenerationBasedOnProbability(std::vector<int> p){
    std::vector<int> tmp;
    int k = 0;
    for (int i = 0; i < p.size(); i++){
        for (int i = p.at(i); i > 0; i--){
            tmp.emplace_back(k);
        }
        k++;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(tmp.begin(), tmp.end(), rng);
    return tmp.at(0);
}
void Floor::init(Player* player, int level){
    this->player = player;
    this->level = level;
    delete td;
    td = new TextDisplay(25, 79);
    mapGenerator("map.txt", theFloor, td);

    std::vector<std::vector<Position>> chambers = chamberConstruction();
    // generate items
    for (int i = 0; i < 5; i++){
        int itemNum = itemNumberRandomGeneration();
        for (int j = 0; j < itemNum; j++){
            CellType item = itemRandomGeneration();
            Position itemPos = randomPosition(chambers.at(i));
            if (item == CellType::gold){
                theFloor.at(itemPos.x).at(itemPos.y).setType(CellType::gold);
                Gold* g = nullptr;
                int goldType = randomGenerationBasedOnProbability({ 2, 1, 1 }); // 2 normal, 1 small, 1 dragon every 4 gold
                if (goldType == 0){
                    Gold* g = new Gold(1, false, nullptr);
                } else if (goldType == 1){
                    Gold* g = new Gold(2, false, nullptr);
                } else if (goldType == 2){
                    Dragon* d = new Dragon();
                    Gold* g = new Gold(6, true, d);
                    std::vector<Position> availablePos;
                    for (int i = -1; i < 2; i++){
                        for (int j = -1; j < 2; j++){
                            if (theFloor.at(itemPos.x + i).at(itemPos.y + j).getCellType() == CellType::tile){
                                availablePos.emplace_back(Position{ itemPos.x + i, itemPos.y + j });
                            }
                        }
                    }
                    Position dragonPos = randomPosition(availablePos);
                    erase(chambers[i], dragonPos);
                    theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
                    theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
                    State dragonState = theFloor.at(dragonPos.x).at(dragonPos.y).getState();
                    dragonState.enemy = d;
                    theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
                    enemies.emplace_back(d);
                }
                State s = theFloor.at(itemPos.x).at(itemPos.y).getState();
                s.gold = g;
                theFloor.at(itemPos.x).at(itemPos.y).setState(s);
                items.emplace_back(g);
            } else if (item == CellType::potion){
                theFloor.at(itemPos.x).at(itemPos.y).setType(CellType::potion);
                int potionType = randomGenerationBasedOnProbability({ 1, 1, 1, 1, 1, 1 }); // 1 RH, 1 BA, 1 BD, 1 PH, 1 WA, 1 WD
                if (potionType == 0){
                    Tempotion* p = new BA(nullptr);
                    // add get and set for Player *component in Decorator
                } else if (potionType == 1){
                    Tempotion* p = new BD(nullptr);
                } else if (potionType == 2){
                    Tempotion* p = new WA(nullptr);
                } else if (potionType == 3){
                    Tempotion* p = new WD(nullptr);
                } else if (potionType == 4){
                    Perpotion* p = new RH(nullptr);
                    // add Perpotion and subclass
                } else if (potionType == 5){
                    Perpotion* p = new LH(nullptr);
                }
            }

        }
    }

    // generate enemies
    for (int i = 0; i < 20; i++){
        int chamberNum = chamberRandomGeneration();
        CellType enemy = enemyRandomGeneration();
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
        theFloor.at(enemyPos.x).at(enemyPos.y).setEnemy(e);
        State s = theFloor.at(enemyPos.x).at(enemyPos.y).getState();
        s.enemy = e;
        theFloor.at(enemyPos.x).at(enemyPos.y).setState(s);
        enemies.emplace_back(e);
    }

}
