#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
template <typename T> class Dragon : public Enemy{
    bool hostile = false;
    T* protectedItem;
public:
    Dragon() : Enemy("Dragon", 150, 20, 20){};
    void setHostile(bool hostile){
        this->hostile = hostile;
    }
    //std::string dlcAttack(Player& whodefend) override;
};




#endif
