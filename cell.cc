#include "cell.h"
#include "state.h"
#include "entity.h"

void Cell::notify(Subject& whoNotified){
    State whoState = whoNotified.getState();
    State thisState = this->getState();
    CellType whoType = whoState.type;
    CellType thisType = thisState.type;
    // common enemies
    if ((thisType == CellType::vampire) || 
    (thisType == CellType::goblin) ||
    (thisType == CellType::phoenix) || 
    (thisType == CellType::troll)) {
        if (whoType == CellType::player) {
            (this->entity)->attack(*(whoState.entity));
        }
    //} else if (thisType == CellType:) {

    //}
    } else if (thisType == CellType::player) {
        for (auto n : whoState.entity->availableDestination) {

        }
    }
}
