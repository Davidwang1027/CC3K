#include "enemy.h"

// libraries for random generation
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>


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

void Enemy::attack(Player& whodefend){
    if (!miss()) {
        int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
        if (whodefend.hasSuit()) {
            damage /= 2;
        }
        whodefend.setHp(this->getHp() - damage);
    }
}
