#include "gold.h"

void Gold::use(Player*& p){
    if (!getIsProtected()){
        p->addGold(value);
    }
    // try - catch? 
}

std::string Gold::getValue() {
    std::string val = std::to_string(value); // e.g 5.5 -> "5.500000"   
    std::string result = "";
    
    for (size_t i = 0; i < val.length() - 7; i++) {
        result += val[i];        
    }
    if (val[val.length() - 6] != '0'){
        result += ".";
        result += val[val.length() - 6];
    }
    return result;
}
