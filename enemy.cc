#include "enemy.h"
#include "player.h"
// libraries for random generation
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>


int Enemy::ceiling(int num){
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

std::string Enemy::attack(Player& whodefend){
    if (!miss()){
        int damage = ceiling((100 / (100 + whodefend.getDef())) * this->getAtk());
        if (whodefend.getSuit()){
            damage /= 2;
        }
        whodefend.setHp(this->getHp() - damage);
        std::string result = this->getName() + " deals " + std::to_string(damage) + " damage to " + whodefend.getName() + ".";
        if (whodefend.getHp() <= 0){
            whodefend.setDead();
            return result + " " + whodefend.getName() + " is dead.";
        }
        return result;
    } else{
        return this->getName() + " missed! Lucky you!";
    }
}
