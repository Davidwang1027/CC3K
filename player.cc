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
    whodefend.setHp(this->getHp() - damage);
}

void Player::move(Direction dir) {
    if (dir == Direction::east) {
        this->setCoords(this->getRow(), this->getCol() + 1);
    } else if (dir == Direction::north) {
        this->setCoords(this->getRow() + 1, this->getCol());
    } else if (dir == Direction::south) {
        this->setCoords(this->getRow() - 1, this->getCol());
    } else{
        this->setCoords(this->getRow(), this->getCol() - 1);
    }
}

void Player::setgold(int plusgold){
    gold = gold + plusgold;
}

int Player::getGold(){
    return gold;
}