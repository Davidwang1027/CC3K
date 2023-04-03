#include "player.h"
#include "entity.h"
#include "direction.h"
#include<iostream>

int ceiling(int num) {
    if (num % 2 == 0) {
        return num;
    } else {
        return num + 1;
    }
}

void Player::attack(Entity& whodefend){
    int damage = ceiling((100/(100 + whodefend.getDef())) * this->getAtk());
    this->setHp(this->getHp() - damage);
}

void Player::move(Direction dir) {
    if () {

    }
}

void Player::setgold(int plusgold){
    gold = gold + plusgold;
}

int Player::getGold(){
    return gold;
}