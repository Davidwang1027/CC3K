#include "enemy.h"
#include "player.h"
// libraries for random generation
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

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
        int damage = ceil((100 / (100 + whodefend.getDef())) * this->getAtk());
        if (whodefend.getSuit()){
            damage /= 2;
        }
        whodefend.setHp(whodefend.getHp() - damage);
        std::string result = this->getName() + " deals " + std::to_string(damage) + " damage to " + whodefend.getName() + "|";
        return result;
    } else{
        return this->getName() + " missed! Lucky you!|";
    }
}
