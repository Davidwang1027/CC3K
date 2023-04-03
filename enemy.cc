#include "enemy.h"

//libraries for random generation
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

//libraries for random generation
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int ceiling(int num){
    if (num % 2 == 0){
        return num;
    } else{
        return num + 1;
    }
}

bool miss() {
    std::vector<int> v = {0,1};

}
void Enemy::attack(Entity& whodefend){
    int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
    whodefend.setHp(this->getHp() - damage);
}

void Enemy::move() {
    //Need random generation
}