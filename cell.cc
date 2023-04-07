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
