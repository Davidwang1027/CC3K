#include "cell.h"
#include "player.h"
class Item{
    bool isProtected = false;
    std::string name;
public:
    Item(bool isProtected, std::string name) : isProtected{ isProtected }, name{ name }{}
    void setIsProtected(){
        this->isProtected = true;
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
