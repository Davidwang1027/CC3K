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
#include "entity.h"
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
                doors.emplace_back(Position{ row,i });
            } else if (c == '#'){
                cell.setType(CellType::passage);
                Position p = { row,i };
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

// Todo: generate suit
void Floor::init(Player*& player, int level, int suitLevel){
    this->player = player;
    this->level = level;
    td = new TextDisplay(25, 79);
    ad = new ActionDisplay();
    mapGenerator("map.txt");

    std::vector<std::vector<Position>> chambers = chamberConstruction();
    // generate suit if suitLevel matches level
    if (suitLevel == level){
        int chamberNum = chamberRandomGeneration();
        Position suitPos = randomPosition(chambers.at(chamberNum));
        // Generate suit
        Suit* s = new Suit(true);
        theFloor.at(suitPos.x).at(suitPos.y).setType(CellType::suit);
        State suitState = { suitPos, CellType::suit, "" };
        items.emplace_back(suitPos);

        // Generate dragon, could be improved by helper function
        Dragon<Suit>* d = new Dragon<Suit>(s);
        std::vector<Position> availablePos;
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                if (theFloor.at(suitPos.x + i).at(suitPos.y + j).getCellType() == CellType::tile){
                    availablePos.emplace_back(Position{ suitPos.x + i, suitPos.y + j });
                }
            }
        }
        Position dragonPos = randomPosition(availablePos);
        erase(chambers[chamberNum], dragonPos);
        theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
        theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
        State dragonState = { dragonPos, CellType::dragon, "" };
        theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
        theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
    }

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
                    g = new Gold(1, false);
                } else if (goldType == 1){
                    g = new Gold(2, false);
                } else if (goldType == 2){
                    g = new Gold(6, true);
                    Dragon<Gold>* d = new Dragon<Gold>(g);
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
                items.emplace_back(itemPos);
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
                    items.emplace_back(itemPos);
                } else if (potionType == 4 || potionType == 5){
                    Perpotion* p = nullptr;
                    if (potionType == 4){
                        p = new RH();
                    } else if (potionType == 5){
                        p = new PH();
                    }
                    theFloor.at(itemPos.x).at(itemPos.y).setPerpotion(p);
                    items.emplace_back(itemPos);
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
        enemies.emplace_back(enemyPos);
        if (i == 10){ //  <<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>
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
    State s = { playerPos, CellType::player, message };
    theFloor.at(playerPos.x).at(playerPos.y).setState(s);
    theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();

}

void Floor::enemyAction(){
    for (int i = 0; i < enemies.size(); i++){
        Position enemyPos = enemies.at(i);
        Cell& ec = theFloor.at(enemyPos.x).at(enemyPos.y);
        Enemy* e = ec.getEnemy();
        CellType enemyType = ec.getCellType();
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                CellType neighbor = theFloor.at(ec.getPos().x + i).at(ec.getPos().y + j).getCellType();
                if (neighbor == CellType::player){
                    Position pPos = theFloor.at(ec.getPos().x + i).at(ec.getPos().y + j).getPos();
                    Player& p = *(theFloor.at(ec.getPos().x + i).at(ec.getPos().y + j).getPlayer());
                    std::string action = e->attack(p);
                    State s = { ec.getPos(),ec.getCellType(), action };
                    ec.setState(s);
                    ec.notifyObservers();
                    if (p.getHp() <= 0){
                        theFloor.at(pPos.x).at(pPos.y).setType(CellType::tile);
                        theFloor.at(pPos.x).at(pPos.y).setState({ pPos, CellType::tile, "You lose!" });
                        theFloor.at(pPos.x).at(pPos.y).notifyObservers();
                        return;
                    }
                } else if (neighbor == CellType::tile){
                    e->addDestination({ ec.getPos().x + i, ec.getPos().y + j });
                }
            }
        }
        // Enemy move randomly
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        std::vector<Position> dest = e->getDestinations();
        std::shuffle(dest.begin(), dest.end(), rng);
        Position newPos = dest.at(0);
        enemies.at(i) = newPos;
        if (stair != nullptr){
            if (stair->getPos().x == ec.getPos().x && stair->getPos().y == ec.getPos().y){
                stair->setEnemy(nullptr);
                stair->setType(CellType::stair);
                stair->setState({ stair->getPos(), CellType::stair, "" });
                stair->notifyObservers();
            }
        } else{
            ec.setEnemy(nullptr);
            ec.setType(CellType::tile);
            ec.setState({ enemyPos, CellType::tile, "" });
            ec.notifyObservers();
        }
        theFloor.at(newPos.x).at(newPos.y).setEnemy(e);
        theFloor.at(newPos.x).at(newPos.y).setType(enemyType);
        theFloor.at(newPos.x).at(newPos.y).setState({ newPos, enemyType, "" });
        theFloor.at(newPos.x).at(newPos.y).notifyObservers();
    }
}

std::string Floor::navigation(Position dir){
    std::string result = "";
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (theFloor.at(dir.x+i).at(dir.y+j).getEnemy() != nullptr) {
                result += " and sees a ";
                result += (theFloor.at(dir.x+i).at(dir.y+j).getEnemy())->getName();
            } else if (theFloor.at(dir.x+i).at(dir.y+j).getCellType() == CellType::gold) {
                if ((theFloor.at(dir.x+i).at(dir.y+j).getGold()->getIsProtected())) {
                    result += "and sees a dragon hoard.";
                } else {
                    result += "and sees a pile of golds.";
                }
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::suit){
                if ((theFloor.at(dir.x + i).at(dir.y + j).getSuit()->getIsProtected())){
                    result += "and sees a Barrier Suit protected by a dragon.";
                } else{
                    result += "and sees a Barrier Suit.";
                }
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::compass){
                result += "and sees a Compass.";
            }
        }
    }
    return result;
}

void Floor::playerMove(Position dir){
    Cell dest = theFloor.at(dir.x).at(dir.y);
    State s = dest.getState();
    if ((s.type == CellType::tile) ||
        (s.type == CellType::passage) ||
        (s.type == CellType::door)){
        dest.setPlayer(player);
        dest.setType(CellType::player);
        std::string nv = navigation(dir);
        dest.setState({ dir, CellType::player, nv });
        dest.notifyObservers();
    } else if (s.type == CellType::compass){
        dest.setPlayer(player);
        std::string display = "You picked up a compass.";
        dest.setState({ dir, CellType::player, display });
        stair->setType(CellType::stair);
        stair->setState({ stair->getPos(), CellType::stair, "The stair appeared!" });
        stair->notifyObservers();
        dest.notifyObservers();
    } else if ((s.type == CellType::gold) && !(dest.getGold()->getIsProtected())){
        dest.setPlayer(player);
        dest.getGold()->use(player);
        std::string display = "You picked up ";
        display += dest.getGold()->getValue();
        display += " Gold.";
        dest.setState({ dir, CellType::player, display });
        dest.notifyObservers();
    } else if ((s.type == CellType::suit) && !(dest.getSuit()->getIsProtected())){
        dest.setPlayer(player);
        dest.getSuit()->use(player);
        std::string display = "You equipped the Barrier Suit.";
        dest.setState({ dir, CellType::player, display });
        dest.notifyObservers();
    } else{
        throw Exception{};
        return;
    }
    // Passage/door recovers
}

void Floor::playerAttack(Position dir){
    Cell& target = theFloor.at(dir.x).at(dir.y);
    CellType ct = target.getCellType();
    if ((ct == CellType::vampire) ||
        (ct == CellType::werewolf) ||
        (ct == CellType::troll) ||
        (ct == CellType::goblin) ||
        (ct == CellType::phoenix)){
        std::string action = player->attack(*(target.getEnemy()));
        State s = { playerPos, CellType::player, action };
        // If enemy is dead, remove it from the floor
        if (target.getEnemy()->getHp() <= 0){
            // Remove enemy from enemies vector
            for (int i = 0; i < enemies.size(); i++){
                if (enemies.at(i).x == dir.x && enemies.at(i).y == dir.y){
                    enemies.erase(enemies.begin() + i);
                }
            }
            // delete enemy
            delete target.getEnemy();
            target.setEnemy(nullptr);
            target.setType(CellType::tile);
            target.setState({ dir, CellType::tile, "" });
            target.notifyObservers();
        }
        theFloor.at(playerPos.x).at(playerPos.y).setState(s);
        theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();
    } else{
        throw Exception{};
        return;
    }
}
void Floor::playerUse(Position dir){
    Cell useCell = theFloor.at(dir.x).at(dir.y);
    if (useCell.getPerpotion() != nullptr){
        useCell.getPerpotion()->use(player);
    } else if (useCell.getTempotion() != nullptr){
        useCell.getTempotion()->use(player);
    } else{
        throw Exception{};
        return;
    }
}

void Floor::goldnavigation(){
    for (auto item : items){
        if (item.){

        }
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
}
