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
            if (s == "Missed"){
                thisState.display.emplace_back("Missed");
                this->setState(thisState);
            }
        } else if (whoType != CellType::tile){
            updateDestinations(*(this->enemy), whoState.pos);
        } else{
            return;
        }
    } else if (thisType == CellType::player){

    }
}
