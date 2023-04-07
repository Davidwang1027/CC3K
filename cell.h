#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "celltype.h"
#include "state.h"
#include "tempotion.h"
#include "perpotion.h"
#include <string>
#include <vector>
class Enemy;
class Player;
class Gold;
class Suit;
class Cell : public Subject<State>{
    Position pos;
    CellType type;
    Player* player = nullptr;
    Enemy* enemy = nullptr;
    Gold* gold = nullptr;
    Suit* suit = nullptr;
    Tempotion* tempotion = nullptr;
    Perpotion* perpotion = nullptr;
    bool stairVisible = false;
    std::string action;
public:
    Cell(Position pos, CellType type, Player* player, Enemy* enemy, Gold* gold, Suit* suit, Tempotion* tempotion, Perpotion* perpotion, bool stairVisible, std::string action) :
        pos{ pos }, type{ type }, player{ player }, enemy{ enemy }, gold{ gold }, suit{ suit }, tempotion{ tempotion }, perpotion{ perpotion }, stairVisible{ stairVisible }, action{ action }{
        this->setState({ type, action });
    }
    Cell();
    void setPos(Position pos){
        this->pos = pos;
    }
    void setPlayer(Player* player){
        this->player = player;
    }
    void setEnemy(Enemy* enemy){
        this->enemy = enemy;
    }
    void setGold(Gold* gold){
        this->gold = gold;
    }
    void setSuit(Suit* suit){
        this->suit = suit;
    }
    void setTempotion(Tempotion* tempotion){
        this->tempotion = tempotion;
    }
    void setPerpotion(Perpotion* perpotion){
        this->perpotion = perpotion;
    }
    void setType(CellType type){
        this->type = type;
    }
    void setStair(bool stairVisible){
        this->stairVisible = stairVisible;
    }
    void setAction(std::string action){
        this->action = action;
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
    Gold* getGold(){
        return gold;
    }
    Suit* getSuit(){
        return suit;
    }
    Tempotion* getTempotion(){
        return tempotion;
    }
    Perpotion* getPerpotion(){
        return perpotion;
    }

    bool getStair(){
        return stairVisible;
    }
    std::string getAction(){
        return action;
    }
};

#endif
