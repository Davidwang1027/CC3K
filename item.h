#ifndef ITEM_H
#define ITEM_H
#include "player.h"
class Item{
    bool isProtected;
    std::string name;
public:
    Item(bool isProtected = false, std::string name = "") : isProtected{ isProtected }, name{ name }{}
    void setIsProtected(bool isProtected){
        this->isProtected = isProtected;
    }
    bool getIsProtected(){
        return isProtected;
    }
    std::string getName(){
        return name;
    }
    void setName(std::string name){
        this->name = name;
    }
    virtual void use(Player*& p) = 0;
};

#endif
