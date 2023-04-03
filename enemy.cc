#include "enemy.h"

int ceiling(int num){
    if (num % 2 == 0){
        return num;
    } else{
        return num + 1;
    }
}

void Enemy::attack(Entity& whodefend){
    int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
    whodefend.setHp(this->getHp() - damage);
}

void Enemy::move() {
    //Need random generation
}