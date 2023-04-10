#include "player.h"
#include "enemy.h"
#include <cmath>


std::string Player::attack(Enemy& whodefend){
    int damage = ceil((100 / (100 + whodefend.getDef())) * this->getAtk());
    whodefend.setHp(whodefend.getHp() - damage);
    std::string result = this->getName() + " deals " + std::to_string(damage) + " damage to " + whodefend.getName() + ".";
    if (whodefend.getHp() <= 0){
        whodefend.setDead();
        if ((whodefend.getName() != "Merchant") && (whodefend.getName() != "Dragon")){
            this->addGold(1);
        }
        return result + " " + whodefend.getName() + " is dead.";
    }
    return result;
}


std::string Player::addGold(float plusgold){
    gold += plusgold;
    return "You picked up " + std::to_string(gold) + " gold.";
}

float Player::getGold(){
    return gold;
}
