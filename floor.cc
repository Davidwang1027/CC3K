#include "floor.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>

int suitrandomGeneration(){
    std::vector<int> v = {0, 1, 2, 3, 4};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int itemnumberrandomGeneration(){
    std::vector<int> v = {0, 1, 2};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

int chamberrandomGeneration(){
    std::vector<int> v = {0, 1, 2, 3, 4};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

CellType enemyrandomGeneration(){
    std::vector<CellType> v = {CellType::vampire, CellType::vampire, CellType::vampire, CellType::werewolf,
    CellType::werewolf, CellType::werewolf, CellType::werewolf, CellType::goblin, CellType::goblin, CellType::goblin,
    CellType::goblin, CellType::goblin, CellType::troll, CellType::troll, CellType::phoenix, CellType::phoenix,
    CellType::merchant, CellType::merchant};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

CellType itemrandomGeneration(){
    std::vector<CellType> v = {CellType::potion, CellType::gold, CellType::gold, CellType::gold, CellType::gold};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(v.begin(), v.end(), rng);
    return *(v.begin());
}

std::ostream& operator<<(std::ostream& out, const Floor& f){
    out << *(f.td);
    return out;
}

//
void mapGenerator(std::string filename, std::vector<std::vector<Cell>>& theFloor, TextDisplay* td){
    std::ifstream file {filename};
    std::string line;
    size_t row = 0;
    while (getline(file, line)){
        std::vector<Cell> temp;
        for (size_t i = 0; i < line.length(); i++){
            Cell cell;
            cell.attach(td);
            char c = line[i];
            if (c == '|'){
                cell.setType(CellType::vWall);
            } else if (c == '-'){
                cell.setType(CellType::hWall);
            } else if (c == '+'){
                cell.setType(CellType::door);
            } else if (c == '#'){
                cell.setType(CellType::passage);
            } else if (c == '.'){
                cell.setType(CellType::tile);
            } else if (c == ' '){
                cell.setType(CellType::empty);
            } else if (c == '\\'){
                cell.setType(CellType::stair);
            }
            cell.setPos({ row, i });
            temp.emplace_back(cell);
        }
        theFloor.emplace_back(temp);
        row++;
    }
}

void Floor::init(Player* player, int level){
    this->player = player;
    this->level = level;
    delete td;
    td = new TextDisplay(25, 79);
    mapGenerator("map.txt", theFloor, td);

}
