#include "player.h"
#include "enemy.h"

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
    std::string result = this->getName() + " deals " + std::to_string(damage) + " damage to " + whodefend.getName() + ".";
    if (whodefend.getHp() <= 0){
        whodefend.setDead();
        return result + " " + whodefend.getName() + " is dead.";
    }
    return result;
}


std::string Player::addGold(float plusgold){
    gold = gold + plusgold;
    return "You picked up " + std::to_string(gold) + " gold.";
}

float Player::getGold(){
    return gold;
}
