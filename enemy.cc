#include "enemy.h"


int ceiling(int num){
    if (num % 2 == 0){
        return num;
    } else{
        return num + 1;
    }
}

bool miss(){
    std::vector<int> v = { 0,1 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    if (*(v.begin()) == 1){
        return true;
    }
    return false;
}

void Enemy::attack(Entity& whodefend){
    if (!miss()) {
        int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
        whodefend.setHp(this->getHp() - damage);
    } 
    
}

void Enemy::move(){
    //Need random generation
}

void Enemy::notify(Subject<State>& whoNotified){
    State s = whoNotified.getState();
    size_t r = s.r;
    size_t c = s.c;
    CellType ct = s.type;
    if (ct == CellType::player){

    }

}
