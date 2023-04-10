#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
template <typename T> class Dragon : public Enemy{
    T* protectedItem;
public:
    explicit Dragon(T* protectedItem) : Enemy("Dragon", 150, 20, 20, false), protectedItem{ protectedItem }{};
    //std::string dlcAttack(Player& whodefend) override;
};




#endif
