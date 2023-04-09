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
    out << "Race: " << p->getName() << " Gold: " << p->getGold() << std::endl;
    out << "HP: " << p->getHp() << std::endl;
    out << "Atk: " << p->getAtk() << std::endl;
    out << "Def: " << p->getDef() << std::endl;
    out << "Action: " << *(f.ad);
    f.ad->clear();
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
        State goldState = { goldPos, CellType::gold, "" };
        theFloor.at(goldPos.x).at(goldPos.y).setState(goldState);
        items.emplace_back(goldPos);
    }


    // generate suit if suitLevel matches level
    if (suitLevel == level){
        int chamberNum = chamberRandomGeneration(10);
        Position suitPos = randomPosition(chambers.at(chamberNum), 10);
        // Generate suit
        Suit* s = new Suit(true, Position{ 114, 514 });
        theFloor.at(suitPos.x).at(suitPos.y).setType(CellType::suit);
        State suitState = { suitPos, CellType::suit, "" };
        items.emplace_back(suitPos);
    }

    // generate dragon 
    int dragonNum = 0;
    for (int i = 0; i < items.size(); i++){
        Cell c = theFloor.at(items.at(i).x).at(items.at(i).y);
        if (c.getCellType() == CellType::gold && c.getGold()->getIsProtected()){
            Position goldPos = items.at(i);
            Gold* g = c.getGold();
            Dragon<Gold>* d = new Dragon<Gold>(g);
            std::vector<Position> availablePos;
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(goldPos.x + i).at(goldPos.y + j).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ goldPos.x + i, goldPos.y + j });
                    }
                }
            }
            Position dragonPos = randomPosition(availablePos, i);
            theFloor.at(goldPos.x).at(goldPos.y).getGold()->setdp(dragonPos);
            erase(chambers[i], dragonPos);
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
            dragonNum++;
        } else if (c.getCellType() == CellType::suit && c.getSuit()->getIsProtected()){
            Position suitPos = items.at(i);
            Suit* s = c.getSuit();
            Dragon<Suit>* d = new Dragon<Suit>(s);
            std::vector<Position> availablePos;
            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){
                    if (theFloor.at(suitPos.x + i).at(suitPos.y + j).getCellType() == CellType::tile){
                        availablePos.emplace_back(Position{ suitPos.x + i, suitPos.y + j });
                    }
                }
            }
            Position dragonPos = randomPosition(availablePos, 10);
            theFloor.at(suitPos.x).at(suitPos.y).getSuit()->setdp(dragonPos);
            erase(chambers[chamberNum], dragonPos);
            theFloor.at(dragonPos.x).at(dragonPos.y).setType(CellType::dragon);
            theFloor.at(dragonPos.x).at(dragonPos.y).setEnemy(d);
            State dragonState = { dragonPos, CellType::dragon, "" };
            theFloor.at(dragonPos.x).at(dragonPos.y).setState(dragonState);
            theFloor.at(dragonPos.x).at(dragonPos.y).notifyObservers();
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
        if (i == 10){ // could be any number
            e->setCompass();
        }
    }



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
        std::vector<Position> dest;
        for (int i = 0; i < e->getDestinations().size(); i++){
            dest.emplace_back(e->getDestinations().at(i));
        }
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
            if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::goblin){
                result += " and sees a Goblin.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::vampire){
                result += " and sees a Vampire.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::troll){
                result += " and sees a Troll.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::dragon){
                result += " and sees a Dragon.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::werewolf){
                result += " and sees a Werewolf.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::merchant){
                result += " and sees a Merchant.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::phoenix){
                result += " and sees a Phoenix.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::potion){
                result += " and sees an unknown potion.";
            } else if (theFloor.at(dir.x + i).at(dir.y + j).getCellType() == CellType::gold){
                if ((theFloor.at(dir.x + i).at(dir.y + j).getGold()->getIsProtected())){
                    result += " and sees a dragon hoard.";
                } else{
                    result += " and sees a pile of golds.";
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
        // display += dest.getGold()->getValue();
        display += " gold.";
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
    // If the player is on a passage/door
    for (int i = 0; i < passages.size(); i++){
        Position p = passages.at(i);
        if (p.x == playerPos.x && p.y == playerPos.y){
            theFloor.at(p.x).at(p.y).setType(CellType::passage);
            theFloor.at(p.x).at(p.y).setState({ p, CellType::passage, "" });
            theFloor.at(p.x).at(p.y).notifyObservers();
            return;
        }
    }
    for (int i = 0; i < doors.size(); i++){
        Position p = doors.at(i);
        if (p.x == playerPos.x && p.y == playerPos.y){
            theFloor.at(p.x).at(p.y).setType(CellType::door);
            theFloor.at(p.x).at(p.y).setState({ p, CellType::door, "" });
            theFloor.at(p.x).at(p.y).notifyObservers();
            return;
        }
    }
    // Recovers the previous tile
    theFloor.at(playerPos.x).at(playerPos.y).setType(CellType::tile);
    theFloor.at(playerPos.x).at(playerPos.y).setState({ playerPos, CellType::tile, "" });
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
            if (ct == CellType::dragon){
                for (int i = 0; i < items.size(); i++){
                    CellType t = theFloor.at(items.at(i).x).at(items.at(i).y).getCellType();
                    if (t == CellType::suit){
                        theFloor.at(items.at(i).x).at(items.at(i).y).getSuit()->setIsProtected(false);
                    }
                    if (t == CellType::gold){
                        theFloor.at(items.at(i).x).at(items.at(i).y).getGold()->setIsProtected(false);
                    }
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
        if (theFloor.at(item.x).at(item.y).getCellType() == CellType::gold){
            if (theFloor.at(item.x).at(item.y).getGold()->getIsProtected()){
                Position dp = theFloor.at(item.x).at(item.y).getGold()->getdp();
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        if (theFloor.at(item.x + i).at(item.y + j).getCellType() == CellType::player){
                            theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(true);
                            return;
                        }
                    }
                }
                theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(false);
            }
        }
    }
}

void Floor::suitnavigation(){
    if (suitLevel != level) return;
    for (auto item : items){
        if (theFloor.at(item.x).at(item.y).getCellType() == CellType::suit){
            if (theFloor.at(item.x).at(item.y).getSuit()->getIsProtected()){
                Position dp = theFloor.at(item.x).at(item.y).getSuit()->getdp();
                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){
                        if (theFloor.at(item.x + i).at(item.y + j).getCellType() == CellType::player){
                            theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(true);
                            return;
                        }
                    }
                }
                theFloor.at(dp.x).at(dp.y).getEnemy()->setHostile(false);
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
}
