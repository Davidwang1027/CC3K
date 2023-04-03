#include "player.h"


int ceiling(int num){
    if (num % 2 == 0){
        return num;
    } else{
        return num + 1;
    }
}

void Player::attack(Entity& whodefend){
    int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
    whodefend.setHp(this->getHp() - damage);
}


void Player::addGold(float plusgold){
    gold = gold + plusgold;
}

float Player::getGold(){
    return gold;
}
