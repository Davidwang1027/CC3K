#include "floor.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <exception>
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
#include "perpotion.h"
#include "ba.h"
#include "bd.h"
#include "wa.h"
#include "wd.h"
#include "rh.h"
#include "ph.h"
#include "gold.h"
#include "suit.h"

class Exception{};

void erase(std::vector<Position>& v, Position p){
    for (size_t i = 0; i < v.size(); i++){
        if (v.at(i).x == p.x && v.at(i).y == p.y){
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
void Floor::mapGenerator(std::string filename){
    std::ifstream file {filename};
    std::string line;
    size_t row = 0;
    while (getline(file, line)){
        std::vector<Cell> temp;
        for (size_t i = 0; i < line.length(); i++){
            Cell cell;
            cell.attach(td);
            cell.attach(ad);
            char c = line[i];
            if (c == '|'){
                cell.setType(CellType::vWall);
            } else if (c == '-'){
                cell.setType(CellType::hWall);
            } else if (c == '+'){
                cell.setType(CellType::door);
                doors.emplace_back(Position{row,i});
            } else if (c == '#'){
                cell.setType(CellType::passage);
                Position p = {row,i};
                passages.emplace_back(p);
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
void Floor::init(Player*& player, int level){
    this->player = player;
    this->level = level;
    td = new TextDisplay(25, 79);
    ad = new ActionDisplay();
    mapGenerator("map.txt");

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
                    State dragonState = { dragonPos, CellType::dragon, "" };
                    theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
                    theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
                }
                theFloor.at(itemPos.x).at(itemPos.y).setGold(g);
                State goldState = { itemPos, CellType::gold, "" };
                theFloor.at(itemPos.x).at(itemPos.y).setState(goldState);
                items.emplace_back(g);
            } else if (item == CellType::potion){
                theFloor.at(itemPos.x).at(itemPos.y).setType(CellType::potion);
                int potionType = randomGenerationBasedOnProbability({ 1, 1, 1, 1, 1, 1 }); // 1 RH, 1 BA, 1 BD, 1 PH, 1 WA, 1 WD
                if (potionType == 0 || potionType == 1 || potionType == 2 || potionType == 3){
                    Tempotion* p = nullptr;
                    if (potionType == 0){
                        p = new BA(nullptr);
                        // add get and set for Player *component in Decorator
                    } else if (potionType == 1){
                        p = new BD(nullptr);
                    } else if (potionType == 2){
                        p = new WA(nullptr);
                    } else if (potionType == 3){
                        p = new WD(nullptr);
                    }
                    theFloor.at(itemPos.x).at(itemPos.y).setTempotion(p);
                    items.emplace_back(p);
                } else if (potionType == 4 || potionType == 5){
                    Perpotion* p = nullptr;
                    if (potionType == 4){
                        p = new RH();
                    } else if (potionType == 5){
                        p = new PH();
                    }
                    theFloor.at(itemPos.x).at(itemPos.y).setPerpotion(p);
                    items.emplace_back(p);
                }
                State s = { itemPos, CellType::potion, "" };
                theFloor.at(itemPos.x).at(itemPos.y).setState(s);
            }
            theFloor.at(itemPos.x).at(itemPos.y).notifyObservers();
        }
    }

    // generate enemies
    for (int i = 0; i < 20; i++){
        int chamberNum = chamberRandomGeneration();
        CellType enemy = enemyRandomGeneration();
        Position enemyPos = randomPosition(chambers.at(chamberNum));
        Enemy* e;
        if (enemy == CellType::vampire){
            e = new Vampire();
        } else if (enemy == CellType::werewolf){
            e = new Werewolf();
        } else if (enemy == CellType::goblin){
            e = new Goblin();
        } else if (enemy == CellType::troll){
            e = new Troll();
        } else if (enemy == CellType::phoenix){
            e = new Phoenix();
        } else if (enemy == CellType::merchant){
            e = new Merchant();
        }
        theFloor.at(enemyPos.x).at(enemyPos.y).setType(enemy);
        theFloor.at(enemyPos.x).at(enemyPos.y).setEnemy(e);
        State s = { enemyPos, enemy , "" };
        theFloor.at(enemyPos.x).at(enemyPos.y).setState(s);
        theFloor.at(enemyPos.x).at(enemyPos.y).notifyObservers();
        enemies.emplace_back(e);
        if (i == 10) { //  <<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>
            e->setCompass();
        }
    }

    //Player generation
    int chamberNum = chamberRandomGeneration();
    playerPos = randomPosition(chambers.at(chamberNum));
    this->player = player;
    theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::player);
    theFloor.at(playerPos.x).at(playerPos.y).setPlayer(player);
    std::string message = player->getName() + " has spawned.";
    State s = {playerPos, CellType::player, message};
    theFloor.at(playerPos.x).at(playerPos.y).setState(s);
    theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();

}

void Floor::enemyAction(){
    for (auto row : theFloor){
        for (auto col : row){
            if (col.getEnemy() != nullptr){
                Enemy* e = col.getEnemy();
                CellType enemyType = col.getCellType();
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        CellType neighbor = theFloor.at(col.getPos().x + i).at(col.getPos().y + j).getCellType();
                        if (neighbor == CellType::player){
                            Position pPos = theFloor.at(col.getPos().x + i).at(col.getPos().y + j).getPos();
                            Player& p = *(theFloor.at(col.getPos().x + i).at(col.getPos().y + j).getPlayer());
                            std::string action = e->attack(p);
                            State s = { col.getPos(),col.getCellType(), action };
                            col.setState(s);
                            col.notifyObservers();
                            if (p.getHp() <= 0){
                                theFloor.at(pPos.x).at(pPos.y).setType(CellType::tile);
                                theFloor.at(pPos.x).at(pPos.y).setState({ pPos, CellType::tile, "You lose!" });
                                theFloor.at(pPos.x).at(pPos.y).notifyObservers();
                                return;
                            }
                        } else if (neighbor == CellType::tile){
                            e->addDestination({ col.getPos().x + i, col.getPos().y + j });
                        }
                    }
                }
                // Enemy move randomly
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine rng{seed};
                std::vector <Position> dest = e->getDestinations();
                std::shuffle(dest.begin(), dest.end(), rng);
                Position newPos = dest.at(0);
                if (stair != nullptr){
                    if (stair->getPos().x == col.getPos().x && stair->getPos().y == col.getPos().y){
                        stair->setEnemy(nullptr);
                        stair->setType(CellType::stair);
                        stair->setState({ stair->getPos(), CellType::stair, "" });
                        stair->notifyObservers();
                    }
                } else{
                    col.setEnemy(nullptr);
                    col.setType(CellType::tile);
                    col.setState({ col.getPos(), CellType::tile, "" });
                    col.notifyObservers();
                }
                theFloor.at(newPos.x).at(newPos.y).setEnemy(e);
                theFloor.at(newPos.x).at(newPos.y).setType(enemyType);
                theFloor.at(newPos.x).at(newPos.y).setState({ newPos, enemyType, "" });
                theFloor.at(newPos.x).at(newPos.y).notifyObservers();
            }
        }
    }
}

std::string navigation(Position dir) {

}
void Floor::playerMove(Position dir){
    Cell dest = theFloor.at(dir.x).at(dir.y);
    State s = dest.getState();
    if ((s.type == CellType::tile) ||
    (s.type == CellType::passage) ||
    (s.type == CellType::door)) {
        dest.setPlayer(player);
        dest.setType(CellType::player);
        std::string nv = navigation(dir);
        dest.setState({ dir, CellType::player, nv });
        dest.notifyObservers();
    } else if (s.type == CellType::compass) {
        dest.setPlayer(player);
        std::string display = "You picked up a compass.";
        dest.setState({ dir, CellType::player, display});
        stair->setType(CellType::stair);
        stair->setState({ stair->getPos(), CellType::stair, "The stair appeared!"});
        stair->notifyObservers();
        dest.notifyObservers();
    } else if ((s.type == CellType::gold) && dest.getGold()->getIsProtected()) {
        dest.setPlayer(player);
        dest.getGold()->use(player);
        std::string display = "You picked up ";
        display += dest.getGold()->getValue();
        display += " Gold.";
        dest.setState({ dir, CellType::player, display});
        dest.notifyObservers();
    } else if ((s.type == CellType::suit) && dest.getSuit()->getIsProtected()) {
        dest.setPlayer(player);
        dest.getSuit()->use(player);
        std::string display = "You equipped the Barrier Suit.";
        dest.setState({ dir, CellType::player, display});
        dest.notifyObservers();
    } else {
        throw Exception{};
        return;
    }

}

bool Floor::isOnStair(){
    if (stair->getPlayer() == nullptr){
        return false;
    }
    return true;
}

Floor::~Floor(){
    delete td;
    for (auto e : enemies){
        delete e;
    }
    for (auto i : items){
        delete i;
    }
}
