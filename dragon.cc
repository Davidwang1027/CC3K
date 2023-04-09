#include "dragon.h"
#include "gold.h"
#include "suit.h"

template <typename T> void Dragon<T>::setHostile(bool hostile){
    this->hostile = hostile;
}

template class Dragon<Gold>;
template class Dragon<Suit>;
