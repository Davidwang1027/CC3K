#include "cell.h"
#include "state.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

void updateDestinations(Entity& e, Position pos){
    std::vector<Position> dest = e.getDestinations();
    for (size_t i = 0; i < dest.size(); i++){
        if ((dest.at(i).x == pos.x) && (dest.at(i).y == pos.y)){
            dest.erase(dest.begin() + i);
            break;
        }
    }
    e.setDestination(dest);
}

void Cell::notify(Subject& whoNotified){
    State whoState = whoNotified.getState();
    State thisState = this->getState();
    CellType whoType = whoState.type;
    CellType thisType = thisState.type;

    // thisType is Enemy
    if ((thisType == CellType::vampire) ||
        (thisType == CellType::goblin) ||
        (thisType == CellType::phoenix) ||
        (thisType == CellType::troll) ||
        (thisType == CellType::werewolf) ||
        (thisType == CellType::merchant) ||
        (thisType == CellType::dragon)){
        if (whoType == CellType::player){     // Enemy attacks player
            std::string s = (this->enemy)->attack(*(whoState.player));
            thisState.display.push_back(s);
            this->setState(thisState);
            this->notifyObservers();
            return;
        } else if (whoType != CellType::tile){
            updateDestinations(*(this->enemy), whoState.pos);
            return;
        } else{
            return;
        }
    }
    // thisType is Player
    else if (thisType == CellType::player){
        if (whoType == CellType::gold){   // Player sees gold
            std::string s = "gold";
            thisState.display.push_back(s);
            this->setState(thisState);
            this->notifyObservers();
            if (whoState.item) {

            }
            return;
        } else if (whoType == CellType::potion) {
            std::string s = "potion";
            thisState.display.push_back(s);
            this->setState(thisState);
            this->notifyObservers();
            updateDestinations(*(this->enemy), whoState.pos);
            return;
        } else if (whoType != CellType::tile) {
            updateDestinations(*(this->enemy), whoState.pos);
            return;
        }
    } else if (thisType == CellType::gold){
        if ()
    }
}
