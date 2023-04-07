#include "cell.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "suit.h"

Cell::Cell(){
    this->setState({ CellType::empty, {} });
}

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
        } else if (whoType != CellType::tile || (whoType == CellType::stair && stairVisible)){
            updateDestinations(*(this->enemy), whoState.pos);
            return;
        } else{
            return;
        }
    }
    // thisType is Player
    else if (thisType == CellType::player){
        if (whoType == CellType::gold){   // Player sees gold
            std::string s;
            if (whoState.gold->getIsProtected()){
                s = "sees a hoard of gold guarded by a dragon";
                thisState.display.push_back(s);
                whoState.gold->getDragon()->setHostile(true);
                updateDestinations(*(this->player), whoState.pos);
            } else{
                s = thisState.gold->getName();
                thisState.display.push_back(s);
            }
            this->setState(thisState);
            this->notifyObservers();
            return;
        } else if (whoType == CellType::suit){
            std::string s;
            if (whoState.suit->getIsProtected()){
                s = "sees a suit of armour guarded by a dragon";
                thisState.display.push_back(s);
                whoState.suit->getDragon()->setHostile(true);
                updateDestinations(*(this->player), whoState.pos);
            } else{
                s = thisState.suit->getName();
                thisState.display.push_back(s);
            }
            this->setState(thisState);
            this->notifyObservers();
            return;
        } else if (whoType == CellType::potion){  // Player sees potion
            std::string s = "potion";
            thisState.display.push_back(s);
            this->setState(thisState);
            updateDestinations(*(this->player), whoState.pos);
            this->notifyObservers();
            return;
        } else if (whoType != CellType::tile && whoType != CellType::stair && whoType != CellType::passage){
            updateDestinations(*(this->player), whoState.pos);
            return;
        } else{
            return;
        }
    }
    // thisType is gold
    else if (thisType == CellType::gold){
        if (whoState.type == CellType::player){
            thisState.gold->getDragon()->setHostile(true);
        }
        return;
    } else if (thisType == CellType::suit){
        if (whoState.type == CellType::player){
            thisState.suit->getDragon()->setHostile(true);
        }
        return;
    } else{
        return;
    }
}
