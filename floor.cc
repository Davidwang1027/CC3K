#include "floor.h"
#include <iomanip>
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
#include "exception.h"


void erase(std::vector<Position>& v, Position p){
    for (size_t i = 0; i < v.size(); i++){
        if (v.at(i).x == p.x && v.at(i).y == p.y){
            v.erase(v.begin() + i);
        }
    }
}
int Floor::suitRandomGeneration(int shufflenumber){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < shufflenumber; i++){
        std::shuffle(v.begin(), v.end(), rng);
    }
    return *(v.begin());
}


int Floor::chamberRandomGeneration(int shufflenumber){
    std::vector<int> v = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < shufflenumber; i++){
        std::shuffle(v.begin(), v.end(), rng);
    }
    return *(v.begin());
}

Position Floor::randomPosition(std::vector<Position>& chamber, int shufflenumber){
    for (int i = 0; i < shufflenumber; i++){
        std::shuffle(chamber.begin(), chamber.end(), rng);
    }
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

    for (size_t i = 3; i < 7; i++){
        for (size_t j = 2; j < 29; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber1.emplace_back(Position{ i, j });
            }
        }
    }

    // chamber 2
    for (size_t i = 3; i < 8; i++){
        for (size_t j = 39; j < 79; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber2.emplace_back(Position{ i, j });
            }
        }
        for (size_t i = 8; i < 14; i++){
            for (size_t j = 58; j < 79; j++){
                if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                    chamber2.emplace_back(Position{ i, j });
                }
            }
        }
    }

    // chamber 3
    for (size_t i = 10; i < 13; i++){
        for (size_t j = 38; j < 52; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber3.emplace_back(Position{ i, j });
            }
        }
    }

    // chamber 4
    for (size_t i = 15; i < 24; i++){
        for (size_t j = 3; j < 27; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber4.emplace_back(Position{ i, j });
            }
        }
    }
    // chamber 5
    for (size_t i = 16; i < 24; i++){
        for (size_t j = 37; j < 79; j++){
            if (theFloor.at(i).at(j).getCellType() == CellType::tile){
                chamber5.emplace_back(Position{ i, j });
            }
        }
    }
    return { chamber1, chamber2, chamber3, chamber4, chamber5 };
}
CellType Floor::enemyRandomGeneration(int shufflenumber){
    std::vector<CellType> v = { CellType::vampire, CellType::vampire, CellType::vampire, CellType::werewolf,
    CellType::werewolf, CellType::werewolf, CellType::werewolf, CellType::goblin, CellType::goblin, CellType::goblin,
    CellType::goblin, CellType::goblin, CellType::troll, CellType::troll, CellType::phoenix, CellType::phoenix,
    CellType::merchant, CellType::merchant };
    for (int i = 0; i < shufflenumber; i++){
        std::shuffle(v.begin(), v.end(), rng);
    }
    return *(v.begin());
}



std::ostream& operator<<(std::ostream& out, const Floor& f){
    out << *(f.td);
    Player* p = f.getPlayer();
    // Player info
    out << "Race: " << p->getName() << " Gold: " << p->getGold() << std::right << std::setw(60) << std::setfill(' ') << "Floor " << f.level << std::endl;
    if (p->getHp() < 0){
        out << "HP: 0" << std::endl;
    } else{
        out << "HP: " << p->getHp() << std::endl;
    }
    out << "Atk: " << p->getAtk() << std::endl;
    out << "Def: " << ceil(p->getDef()) << std::endl;
    out << "Action: " << *(f.ad);
    (f.ad)->clear();
    return out;
}

// 
void Floor::mapGenerator(std::string filename){
    std::ifstream file {filename};
    std::string line;
    size_t row = 0;

    for (size_t i = 0; i < 25; i++){
        std::vector<Cell> temp;
        for (size_t j = 0; j < 79; j++){
            Cell cell;
            cell.attach(td);
            cell.attach(ad);
            temp.emplace_back(cell);
        }
        theFloor.emplace_back(temp);
    }

    while (getline(file, line)){
        for (size_t i = 0; i < line.length(); i++){
            Cell& cell = theFloor.at(row).at(i);
            char c = line[i];
            Position p = { row, i };
            State s;
            if (c == '|'){
                cell.setType(CellType::vWall);
                s = { p, CellType::vWall, "" };
            } else if (c == '-'){
                cell.setType(CellType::hWall);
                s = { p, CellType::hWall, "" };
            } else if (c == '+'){
                cell.setType(CellType::door);
                doors.emplace_back(Position{ row,i });
                s = { p, CellType::door, "" };
            } else if (c == '#'){
                cell.setType(CellType::passage);
                passages.emplace_back(p);
                s = { p, CellType::passage, "" };
            } else if (c == '.'){
                cell.setType(CellType::tile);
                s = { p, CellType::tile, "" };
            } else if (c == ' '){
                cell.setType(CellType::empty);
                s = { p, CellType::empty, "" };
            } else if (c == '\\'){
                cell.setType(CellType::stair);
                s = { p, CellType::stair, "" };
            } else if (c == '0'){
                cell.setType(CellType::potion);
                Perpotion* rh = new RH();
                cell.setPerpotion(rh);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '1'){
                cell.setType(CellType::potion);
                Tempotion* ba = new BA(nullptr);
                cell.setTempotion(ba);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '2'){
                cell.setType(CellType::potion);
                Tempotion* bd = new BD(nullptr);
                cell.setTempotion(bd);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '3'){
                cell.setType(CellType::potion);
                Perpotion* ph = new PH();
                cell.setPerpotion(ph);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '4'){
                cell.setType(CellType::potion);
                Tempotion* wa = new WA(nullptr);
                cell.setTempotion(wa);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '5'){
                cell.setType(CellType::potion);
                Tempotion* wd = new WD(nullptr);
                cell.setTempotion(wd);
                s = { p, CellType::potion, "" };
                items.emplace_back(p);
            } else if (c == '6'){
                cell.setType(CellType::gold);
                Gold* g = new Gold(1, false, Position{ 114, 514 });
                cell.setGold(g);
                s = { p, CellType::gold, "" };
                items.emplace_back(p);
            } else if (c == '7'){
                cell.setType(CellType::gold);
                Gold* g = new Gold(2, false, Position{ 114, 514 });
                cell.setGold(g);
                s = { p, CellType::gold, "" };
                items.emplace_back(p);
            } else if (c == '8'){
                cell.setType(CellType::gold);
                Gold* g = new Gold(4, false, Position{ 114, 514 });
                cell.setGold(g);
                s = { p, CellType::gold, "" };
                items.emplace_back(p);
            } else if (c == '9'){
                cell.setType(CellType::gold);
                Gold* g = new Gold(6, true, Position{ 114, 514 });
                cell.setGold(g);
                s = { p, CellType::gold, "" };
                items.emplace_back(p);
            }
            cell.setPos({ row, i });
            cell.setState(s);
            cell.notifyObservers();
        }
        row++;
    }
}

int Floor::randomGenerationBasedOnProbability(std::vector<int> p, int shufflenumber){
    std::vector<int> tmp;
    int k = 0;
    for (int i = 0; i < p.size(); i++){
        for (int j = p.at(i); j > 0; j--){
            tmp.emplace_back(k);
        }
        k++;
    }
    for (int i = 0; i < shufflenumber; i++){
        std::shuffle(tmp.begin(), tmp.end(), rng);
    }
    return tmp.at(0);
}


void Floor::init(Player*& player, int level, int suitLevel, std::default_random_engine rng){
    this->player = player;
    this->suitLevel = suitLevel;
    this->level = level;
    this->rng = rng;
    td = new TextDisplay(25, 79);
    ad = new ActionDisplay();
    mapGenerator("map.txt");
    std::vector<std::vector<Position>> chambers = chamberConstruction();


    // Player generation
    int chamberNum = chamberRandomGeneration(1);
    playerPos = randomPosition(chambers.at(chamberNum), 1);
    this->player = player;
    erase(chambers.at(chamberNum), playerPos);
    theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::player);
    theFloor.at(playerPos.x).at(playerPos.y).setPlayer(player);
    std::string message = player->getName() + " has spawned.";
    State s = { playerPos, CellType::player, message };
    theFloor.at(playerPos.x).at(playerPos.y).setState(s);
    theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();


    // Stair generation
    chamberNum = chamberRandomGeneration(2);
    Position stairPos = randomPosition(chambers.at(chamberNum), 1);
    stair = &(theFloor.at(stairPos.x).at(stairPos.y));


    // Generate potion
    for (int i = 0; i < 10; i++){
        chamberNum = chamberRandomGeneration(i);
        Position potionPos = randomPosition(chambers.at(chamberNum), i);
        int potionType = randomGenerationBasedOnProbability({ 1, 1, 1, 1, 1, 1 }, i); // 1 RH, 1 BA, 1 BD, 1 PH, 1 WA, 1 WD
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
            theFloor.at(potionPos.x).at(potionPos.y).setTempotion(p);
        } else if (potionType == 4 || potionType == 5){
            Perpotion* p = nullptr;
            if (potionType == 4){
                p = new RH();
            } else if (potionType == 5){
                p = new PH();
            }
            theFloor.at(potionPos.x).at(potionPos.y).setPerpotion(p);
        }
        items.emplace_back(potionPos);
        State potionState = { potionPos, CellType::potion, "" };
        theFloor.at(potionPos.x).at(potionPos.y).setState(potionState);
        theFloor.at(potionPos.x).at(potionPos.y).setType(CellType::potion);
        theFloor.at(potionPos.x).at(potionPos.y).notifyObservers();
    }


    // Generate gold
    for (int i = 0; i < 10; i++){
        chamberNum = chamberRandomGeneration(i);
        Position goldPos = randomPosition(chambers.at(chamberNum), i);
        int goldType = randomGenerationBasedOnProbability({ 5, 2, 1 }, i); // 5 normal, 2 small, 1 dragon
        Gold* g = nullptr;
        if (goldType == 0){
            g = new Gold(1, false, Position{ 114, 514 });
        } else if (goldType == 1){
            g = new Gold(2, false, Position{ 114, 514 });
        } else if (goldType == 2){
            g = new Gold(6, true, Position{ 114, 514 });
        }
        theFloor.at(goldPos.x).at(goldPos.y).setGold(g);
        items.emplace_back(goldPos);
        State goldState = { goldPos, CellType::gold, "" };
        theFloor.at(goldPos.x).at(goldPos.y).setState(goldState);
        theFloor.at(goldPos.x).at(goldPos.y).setType(CellType::gold);
        theFloor.at(goldPos.x).at(goldPos.y).notifyObservers();

    }


    // generate suit if suitLevel matches level
    if (suitLevel == level){
        int chamberNum = chamberRandomGeneration(10);
        Position suitPos = randomPosition(chambers.at(chamberNum), 10);
        // Generate suit
        Suit* s = new Suit(true, Position{ 114, 514 });
        theFloor.at(suitPos.x).at(suitPos.y).setType(CellType::suit);
        State suitState = { suitPos, CellType::suit, "" };
        theFloor.at(suitPos.x).at(suitPos.y).setState(suitState);
        theFloor.at(suitPos.x).at(suitPos.y).setSuit(s);
        theFloor.at(suitPos.x).at(suitPos.y).notifyObservers();
        items.emplace_back(suitPos);
    }

    // generate dragon 
    int dragonNum = 0;
    for (int i = 0; i < items.size(); i++){
        Cell& c = theFloor.at(items.at(i).x).at(items.at(i).y);
        if (c.getCellType() == CellType::gold && c.getGold()->getIsProtected()){
            Position goldPos = items.at(i);
            Gold* g = c.getGold();
            Dragon<Gold>* d = new Dragon<Gold>(g);
            std::vector<Position> availablePos = {};
            for (int k = -1; k < 2; k++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(goldPos.x + k).at(goldPos.y + j).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ goldPos.x + k, goldPos.y + j });
                    }
                }
            }
            if (availablePos.size() == 0){
                g->setIsProtected(false);
                continue;
            }
            Position dragonPos = randomPosition(availablePos, i);
            theFloor.at(goldPos.x).at(goldPos.y).getGold()->setdp(dragonPos);
            for (int k = 0; k < 5; k++){
                for (int j = 0; j < chambers.at(k).size(); j++){
                    if ((chambers.at(k).at(j).x == dragonPos.x) && (chambers.at(k).at(j).y == dragonPos.y)){
                        chambers.at(k).erase(chambers.at(k).begin() + j);
                    }
                }
            }
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
            enemies.emplace_back(dragonPos);
            dragonNum++;
        } else if (c.getCellType() == CellType::suit && c.getSuit()->getIsProtected()){
            Position suitPos = items.at(i);
            Suit* s = c.getSuit();
            Dragon<Suit>* d = new Dragon<Suit>(s);
            std::vector<Position> availablePos = {};
            for (int k = -1; k < 2; k++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(suitPos.x + k).at(suitPos.y + k).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ suitPos.x + k, suitPos.y + j });
                    }
                }
            }
            if (availablePos.size() == 0){
                s->setIsProtected(false);
                continue;
            }
            Position dragonPos = randomPosition(availablePos, 10);
            theFloor.at(suitPos.x).at(suitPos.y).getSuit()->setdp(dragonPos);
            for (int k = 0; k < 5; k++){
                for (int j = 0; j < chambers.at(k).size(); j++){
                    if ((chambers.at(k).at(j).x == dragonPos.x) && (chambers.at(k).at(j).y == dragonPos.y)){
                        chambers.at(k).erase(chambers.at(k).begin() + j);
                    }
                }
            }
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
            enemies.emplace_back(dragonPos);
            dragonNum++;
        }

    }

    // generate enemies
    for (int i = 0; i < 20 - dragonNum; i++){
        chamberNum = chamberRandomGeneration(i);
        CellType enemy = enemyRandomGeneration(i);
        Position enemyPos = randomPosition(chambers.at(chamberNum), i);
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
    }
    std::vector<Position> enemiesPositon = enemies;
    std::shuffle(enemiesPositon.begin(), enemiesPositon.end(), rng);
    for (int i = 0; i < enemiesPositon.size(); i++){
        Cell& c = theFloor.at(enemiesPositon.at(i).x).at(enemiesPositon.at(i).y);
        if (c.getCellType() != CellType::merchant){
            c.getEnemy()->setCompass();
            return;
        }
    }
}

void Floor::init(Player*& player, int level, int suitLevel, std::default_random_engine rng, const std::string filename){
    this->player = player;
    this->suitLevel = suitLevel;
    this->level = level;
    this->rng = rng;
    td = new TextDisplay(25, 79);
    ad = new ActionDisplay();
    mapGenerator(filename);
    std::vector<std::vector<Position>> chambers = chamberConstruction();

    for (int i = 0; i < items.size(); i++){
        Position itemPos = items.at(i);
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < chambers.at(j).size(); k++){
                if ((chambers.at(j).at(k).x == itemPos.x) && (chambers.at(j).at(k).y == itemPos.y)){
                    erase(chambers.at(j), itemPos);
                }
            }
        }
    }


    // Player generation
    int chamberNum = chamberRandomGeneration(1);
    playerPos = randomPosition(chambers.at(chamberNum), 1);
    this->player = player;
    erase(chambers.at(chamberNum), playerPos);
    theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::player);
    theFloor.at(playerPos.x).at(playerPos.y).setPlayer(player);
    std::string message = player->getName() + " has spawned.";
    State s = { playerPos, CellType::player, message };
    theFloor.at(playerPos.x).at(playerPos.y).setState(s);
    theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();

    // Stair generation
    chamberNum = chamberRandomGeneration(2);
    Position stairPos = randomPosition(chambers.at(chamberNum), 1);
    stair = &(theFloor.at(stairPos.x).at(stairPos.y));


    // generate suit if suitLevel matches level
    if (suitLevel == level){
        int chamberNum = chamberRandomGeneration(10);
        Position suitPos = randomPosition(chambers.at(chamberNum), 10);
        // Generate suit
        Suit* s = new Suit(true, Position{ 114, 514 });
        theFloor.at(suitPos.x).at(suitPos.y).setType(CellType::suit);
        State suitState = { suitPos, CellType::suit, "" };
        theFloor.at(suitPos.x).at(suitPos.y).setState(suitState);
        theFloor.at(suitPos.x).at(suitPos.y).setSuit(s);
        theFloor.at(suitPos.x).at(suitPos.y).notifyObservers();
        items.emplace_back(suitPos);
    }

    // generate dragon 
    int dragonNum = 0;
    for (int i = 0; i < items.size(); i++){
        Cell& c = theFloor.at(items.at(i).x).at(items.at(i).y);
        if (c.getCellType() == CellType::gold && c.getGold()->getIsProtected()){
            Position goldPos = items.at(i);
            Gold* g = c.getGold();
            Dragon<Gold>* d = new Dragon<Gold>(g);
            std::vector<Position> availablePos = {};
            for (int k = -1; k < 2; k++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(goldPos.x + k).at(goldPos.y + j).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ goldPos.x + k, goldPos.y + j });
                    }
                }
            }
            if (availablePos.size() == 0){
                g->setIsProtected(false);
                continue;
            }
            Position dragonPos = randomPosition(availablePos, i);
            theFloor.at(goldPos.x).at(goldPos.y).getGold()->setdp(dragonPos);
            for (int k = 0; k < 5; k++){
                for (int j = 0; j < chambers.at(k).size(); j++){
                    if ((chambers.at(k).at(j).x == dragonPos.x) && (chambers.at(k).at(j).y == dragonPos.y)){
                        chambers.at(k).erase(chambers.at(k).begin() + j);
                    }
                }
            }
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
            enemies.emplace_back(dragonPos);
            dragonNum++;
        } else if (c.getCellType() == CellType::suit && c.getSuit()->getIsProtected()){
            Position suitPos = items.at(i);
            Suit* s = c.getSuit();
            Dragon<Suit>* d = new Dragon<Suit>(s);
            std::vector<Position> availablePos = {};
            for (int k = -1; k < 2; k++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(suitPos.x + k).at(suitPos.y + k).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ suitPos.x + k, suitPos.y + j });
                    }
                }
            }
            if (availablePos.size() == 0){
                s->setIsProtected(false);
                continue;
            }
            Position dragonPos = randomPosition(availablePos, 10);
            theFloor.at(suitPos.x).at(suitPos.y).getSuit()->setdp(dragonPos);
            for (int k = 0; k < 5; k++){
                for (int j = 0; j < chambers.at(k).size(); j++){
                    if ((chambers.at(k).at(j).x == dragonPos.x) && (chambers.at(k).at(j).y == dragonPos.y)){
                        chambers.at(k).erase(chambers.at(k).begin() + j);
                    }
                }
            }
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
            enemies.emplace_back(dragonPos);
            dragonNum++;
        }

    }

    // generate enemies
    for (int i = 0; i < 20 - dragonNum; i++){
        chamberNum = chamberRandomGeneration(i);
        CellType enemy = enemyRandomGeneration(i);
        Position enemyPos = randomPosition(chambers.at(chamberNum), i);
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
    }
    std::vector<Position> enemiesPositon = enemies;
    std::shuffle(enemiesPositon.begin(), enemiesPositon.end(), rng);
    for (int i = 0; i < enemiesPositon.size(); i++){
        Cell& c = theFloor.at(enemiesPositon.at(i).x).at(enemiesPositon.at(i).y);
        if (c.getCellType() != CellType::merchant){
            c.getEnemy()->setCompass();
            return;
        }
    }

}


void Floor::enemyAction(){
    for (int i = 0; i < enemies.size(); i++){
        bool attacked = false;
        Position enemyPos = enemies.at(i);
        Cell& ec = theFloor.at(enemyPos.x).at(enemyPos.y);
        Enemy* e = ec.getEnemy();
        CellType enemyType = ec.getCellType();
        e->clearDestinations();
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                if ((i == 0) && (j == 0)){ continue; }
                CellType neighbor = theFloor.at(enemyPos.x + i).at(enemyPos.y + j).getCellType();
                if ((neighbor == CellType::player) && (e->getHostile())){
                    std::string action = e->attack(*player);
                    State s = { enemyPos,ec.getCellType(), action };
                    ec.setState(s);
                    ec.notifyObservers();
                    if (player->getHp() <= 0){
                        theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::tile);
                        theFloor.at(playerPos.x).at(playerPos.y).setState({ playerPos, CellType::tile, "" });
                        theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();
                    }
                    attacked = true;
                    //break;
                } else if (neighbor == CellType::tile){
                    e->addDestination(Position{ enemyPos.x + i, enemyPos.y + j });
                }
            }
        }
        if (attacked || enemyType == CellType::dragon){
            continue;
        }
        // Enemy move randomly
        std::vector<Position> dest = e->getDestinations();
        std::shuffle(dest.begin(), dest.end(), rng);
        Position newPos = dest.at(0);
        enemies.at(i) = newPos;
        ec.setEnemy(nullptr);
        ec.setType(CellType::tile);
        ec.setState({ enemyPos, CellType::tile, "" });
        ec.notifyObservers();
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
            if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::goblin){
                result += "sees a Goblin|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::vampire){
                result += "sees a Vampire|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::troll){
                result += "sees a Troll|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::dragon){
                result += "sees a Dragon|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::werewolf){
                result += "sees a Werewolf|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::merchant){
                result += "sees a Merchant|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::phoenix){
                result += "sees a Phoenix|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::potion){
                result += "sees an unknown potion|";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::gold){
                if ((theFloor.at(dir.x + i).at(dir.y + j).getGold()->getIsProtected())){
                    result += "sees a dragon hoard|";
                } else{
                    result += "sees a pile of golds|";
                }
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::suit){
                if ((theFloor.at(dir.x + i).at(dir.y + j).getSuit()->getIsProtected())){
                    result += "sees a Barrier Suit protected by a dragon|";
                } else{
                    result += "sees a Barrier Suit|";
                }
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::compass){
                result += "sees a Compass|";
            }
        }
    }
    return result;
}

void Floor::playerMove(Position dir){
    std::string direction = "";
    if (dir.y == playerPos.y){
        if (dir.x == playerPos.x - 1){
            direction = "north";
        } else{
            direction = "south";
        }
    } else if (dir.x == playerPos.x){
        if (dir.y == playerPos.y - 1){
            direction = "west";
        } else{
            direction = "east";
        }
    } else if (dir.y == playerPos.y - 1){
        if (dir.x == playerPos.x - 1){
            direction = "north west";
        } else{
            direction = "south west";
        }
    } else{
        if (dir.x == playerPos.x - 1){
            direction = "north east";
        } else{
            direction = "south east";
        }
    }
    std::string action = "PC moves " + direction + "|";
    Cell& dest = theFloor.at(dir.x).at(dir.y);
    State s = dest.getState();
    if ((s.type == CellType::tile) ||
        (s.type == CellType::passage) ||
        (s.type == CellType::door) ||
        (s.type == CellType::stair)){
        dest.setPlayer(player);
        dest.setType(CellType::player);
        std::string nv = navigation(dir);
        dest.setState({ dir, CellType::player, nv });
        dest.notifyObservers();
    } else if (s.type == CellType::compass){
        dest.setPlayer(player);
        std::string display = "You picked up a compass.|";
        dest.setState({ dir, CellType::player, display });
        dest.setType(CellType::player);
        stair->setType(CellType::stair);
        stair->setState({ stair->getPos(), CellType::stair, " The stair appeared!|" });
        stair->notifyObservers();
        dest.notifyObservers();
    } else if ((s.type == CellType::gold) && !(dest.getGold()->getIsProtected())){
        dest.setPlayer(player);
        dest.setType(CellType::player);
        dest.getGold()->use(player);
        std::string display = " You picked up ";
        display += dest.getGold()->getValue();
        display += " gold|";
        dest.setState({ dir, CellType::player, display });
        dest.setGold(nullptr);
        erase(items, dest.getPos());
        dest.notifyObservers();
    } else if ((s.type == CellType::suit) && !(dest.getSuit()->getIsProtected())){
        dest.setPlayer(player);
        dest.setType(CellType::player);
        dest.getSuit()->use(player);
        std::string display = "You equipped the Barrier Suit|";
        dest.setState({ dir, CellType::player, display });
        dest.setSuit(nullptr);
        erase(items, dest.getPos());
        dest.notifyObservers();
    } else{
        throw Exception{};
        return;
    }
    // Passage/door recovers
    // If the player is on a passage/door
    for (int i = 0; i < passages.size(); i++){
        Position p = passages.at(i);
        if ((p.x == playerPos.x) && (p.y == playerPos.y)){
            theFloor.at(p.x).at(p.y).setPlayer(nullptr);
            theFloor.at(p.x).at(p.y).setType(CellType::passage);
            theFloor.at(p.x).at(p.y).setState({ p, CellType::passage, action });
            theFloor.at(p.x).at(p.y).notifyObservers();
            playerPos = dir;
            return;
        }
    }
    for (int i = 0; i < doors.size(); i++){
        Position p = doors.at(i);
        if ((p.x == playerPos.x) && (p.y == playerPos.y)){
            theFloor.at(p.x).at(p.y).setPlayer(nullptr);
            theFloor.at(p.x).at(p.y).setType(CellType::door);
            theFloor.at(p.x).at(p.y).setState({ p, CellType::door, action });
            theFloor.at(p.x).at(p.y).notifyObservers();
            playerPos = dir;
            return;
        }
    }
    // Recovers the previous tile
    theFloor.at(playerPos.x).at(playerPos.y).setPlayer(nullptr);
    theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::tile);
    theFloor.at(playerPos.x).at(playerPos.y).setState({ playerPos, CellType::tile, action });
    theFloor.at(playerPos.x).at(playerPos.y).notifyObservers();
    playerPos.x = dir.x;
    playerPos.y = dir.y;

}

void Floor::playerAttack(Position dir){
    Cell& target = theFloor.at(dir.x).at(dir.y);
    CellType ct = target.getCellType();
    if ((ct == CellType::vampire) ||
        (ct == CellType::werewolf) ||
        (ct == CellType::troll) ||
        (ct == CellType::goblin) ||
        (ct == CellType::phoenix) ||
        (ct == CellType::merchant) ||
        (ct == CellType::dragon)){
        std::string action = player->attack(*(target.getEnemy()));
        State s = { playerPos, CellType::player, action };
        if (ct == CellType::merchant){
            for (int i = 0; i < enemies.size(); i++){
                CellType t = theFloor.at(enemies.at(i).x).at(enemies.at(i).y).getCellType();
                if (t == CellType::merchant){
                    theFloor.at(enemies.at(i).x).at(enemies.at(i).y).getEnemy()->setHostile(true);
                }
            }
        }
        // If enemy is dead, remove it from the floor
        if (target.getEnemy()->getHp() <= 0){
            // Remove enemy from enemies vector
            for (int i = 0; i < enemies.size(); i++){
                if (enemies.at(i).x == dir.x && enemies.at(i).y == dir.y){
                    enemies.erase(enemies.begin() + i);
                }
            }
            if (ct == CellType::merchant){
                Gold* g = new Gold{ 4, false, Position{114, 514} };
                items.emplace_back(dir);
                target.setGold(g);
                target.setType(CellType::gold);
                target.setState({ dir, CellType::gold, "Merchant is dead and dropped a pile of gold|" });
                target.notifyObservers();
                return;
            }

            if (ct == CellType::dragon){
                Position protectedPos;
                Gold* gold = nullptr;
                Suit* suit = nullptr;
                for (int i = 0; i < items.size(); i++){
                    Position p = items.at(i);
                    gold = theFloor.at(p.x).at(p.y).getGold();
                    suit = theFloor.at(p.x).at(p.y).getSuit();
                    bool goldIsProtected = false;
                    bool suitIsProtected = false;
                    if (gold != nullptr){
                        goldIsProtected = gold->getIsProtected();
                    }
                    if (suit != nullptr){
                        suitIsProtected = suit->getIsProtected();
                    }
                    if (goldIsProtected){
                        protectedPos = gold->getdp();
                    }
                    if (suitIsProtected){
                        protectedPos = suit->getdp();
                    }
                    if ((protectedPos.x == dir.x) && (protectedPos.y == dir.y)){
                        if (goldIsProtected){
                            gold->setIsProtected(false);
                            gold->setdp({ 114, 514 });
                        }
                        if (suitIsProtected){
                            suit->setIsProtected(false);
                            suit->setdp({ 114, 514 });
                        }
                    }
                }
            }
            if (target.getEnemy()->getCompass()){
                delete target.getEnemy();
                target.setEnemy(nullptr);
                target.setType(CellType::compass);
                target.setState({ dir, CellType::compass, "A compass has dropped!|" });
                target.notifyObservers();
                return;
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

bool Floor::playerUse(Position dir){
    bool usetemp = false;
    std::string potionName;
    Cell& p = theFloor.at(dir.x).at(dir.y);
    if (p.getPerpotion() != nullptr){
        p.getPerpotion()->use(player);
        potionName = p.getPerpotion()->getName();
        delete p.getPerpotion();
        p.setPerpotion(nullptr);
    } else if (p.getTempotion() != nullptr){
        p.getTempotion()->use(player);
        potionName = p.getTempotion()->getPotionName();
        usetemp = true;
        p.setTempotion(nullptr);
    } else{
        throw Exception{};
    }
    std::string message = "PC uses a " + potionName + " potion|";
    p.setType(CellType::tile);
    p.setState({ dir, CellType::tile, message });
    erase(items, dir);
    p.notifyObservers();
    return usetemp;
}

void Floor::goldnavigation(){
    for (auto item : items){
        bool detected = false;
        if (theFloor.at(item.x).at(item.y).getCellType() == CellType::gold){
            if (theFloor.at(item.x).at(item.y).getGold()->getIsProtected()){
                Position dp = theFloor.at(item.x).at(item.y).getGold()->getdp();
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        if (theFloor.at(item.x + i).at(item.y + j).getCellType() == CellType::player){
                            theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(true);
                            detected = true;
                        }
                    }
                }
                if (!detected){
                    theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(false);
                }
            }
        }
    }
}

void Floor::suitnavigation(){
    if (suitLevel != level) return;
    for (auto item : items){
        bool detected = false;
        if (theFloor.at(item.x).at(item.y).getCellType() == CellType::suit){
            if (theFloor.at(item.x).at(item.y).getSuit()->getIsProtected()){
                Position dp = theFloor.at(item.x).at(item.y).getSuit()->getdp();
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        if (theFloor.at(item.x + i).at(item.y + j).getCellType() == CellType::player){
                            theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(true);
                            detected = true;
                        }
                    }
                }
                if (!detected){
                    theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(false);
                }
            }
        }
    }
}

bool Floor::isOnStair(){
    if (stair->getPlayer() == nullptr){
        return false;
    }
    return true;
}

bool Floor::isWon(){
    if (this->isOnStair() && level == 5){
        return true;
    }
    return false;
}
bool Floor::isLost(){
    if (player->getHp() <= 0){
        return true;
    }
    return false;
}
Floor::~Floor(){
    delete td;
    delete ad;
}
