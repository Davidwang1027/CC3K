#include "player.h"


int ceiling(int num){
    if (num % 2 == 0){
        return num;
    } else{
        return num + 1;
    }
}

std::string Player::attack(Enemy& whodefend){
    int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
    whodefend.setHp(this->getHp() - damage);
    return std::to_string(damage);
}


std::string Player::addGold(float plusgold){
    gold = gold + plusgold;
    return std::to_string(gold);
}

float Player::getGold(){
    return gold;
}
