#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
template <typename T> class Dragon : public Enemy{
    bool hostile = false;
    T* protectedItem;
public:
    explicit Dragon(T* protectedItem) : Enemy("Dragon", 150, 20, 20), protectedItem{ protectedItem }{};
    void setHostile(bool hostile) override;
    //std::string dlcAttack(Player& whodefend) override;
};




#endif
