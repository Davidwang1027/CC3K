#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "observer.h"
#include "celltype.h"
#include "state.h"

class Entity;
class Item;
class Cell : public Subject<State>, public Observer<State>{
    std::size_t r, c;
    CellType type;
    Entity* entity = nullptr;
    Item* item = nullptr;
    bool stairVisible = false;
public:
    Cell(std::size_t r, std::size_t c, CellType type, Entity* entity, Item* item, bool stairVisible) :
        r{ r }, c{ c }, type{ type }, entity{ entity }, item{ item }, stairVisible{ stairVisible }{
        this->setState({ r, c, type, entity, item, stairVisible });
    };
    void setCoords(std::size_t r, std::size_t c){
        this->r = r;
        this->c = c;
    }
    void setEntity(Entity* entity){
        this->entity = entity;
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
    std::size_t getRow(){
        return r;
    }
    std::size_t getCol(){
        return c;
    }
    CellType getCellType(){
        return type;
    }
    Entity* getEntity(){
        return entity;
    }
    Item* getItem(){
        return item;
    }
    bool getStair(){
        return stairVisible;
    }
    void notify(Subject& whoNotified) override;
};

#endif
