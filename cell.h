#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "celltype.h"
#include "state.h"
#include <string>
#include <vector>
class Enemy;
class Player;
class Item;
class Cell : public Subject<State>, public Observer<State>{
    Position pos;
    CellType type;
    Player* player = nullptr;
    Enemy* enemy = nullptr;
    Item* item = nullptr;
    bool stairVisible = false;
    std::vector<std::string> display;
public:
    Cell(Position pos, CellType type, Player* player, Enemy* enemy, Item* item, bool stairVisible, std::vector<std::string> display) :
        pos{ pos }, type{ type }, player{ player }, enemy{ enemy }, item{ item }, stairVisible{ stairVisible }, display{ display }{
        this->setState({ pos, type, player, enemy, item, stairVisible, display });
    }
    void setPos(Position pos){
        this->pos = pos;
    }
    void setPlayer(Player* player){
        this->player = player;
    }
    void setEnemy(Enemy* enemy){
        this->enemy = enemy;
    }
    void setItem(Item* item){
        this->item = item;
    }
    void setType(CellType type){
        this->type = type;
    }
    void setStair(bool stairVisible){
        this->stairVisible = stairVisible;
    }
    void setDisplay(std::vector<std::string> display){
        this->display = display;
    }
    Position getPos(){
        return pos;
    }
    CellType getCellType(){
        return type;
    }
    Player* getPlayer(){
        return player;
    }
    Enemy* getEnemy(){
        return enemy;
    }
    Item* getItem(){
        return item;
    }
    bool getStair(){
        return stairVisible;
    }
    std::vector<std::string> getDisplay(){
        return display;
    }
    void notify(Subject& whoNotified) override;
};

#endif
