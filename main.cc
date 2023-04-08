#include "floor.h"
#include "exception.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include <iostream>

int main(){
    std::string cmd;
    std::vector<Floor> floors;
    Player *p;
    std::cout << "Please select your race (h, e, d, o) : ";

    try {
        std::cin >> cmd;
        if (cmd == "h") {
            p = new Human();
        } else if (cmd == "e") {
            p = new Elf();
        } else if (cmd == "d") {
            p = new Dwarf();
        } else if (cmd == "o") {
            p = new Orc();
        } else {
            throw Exception{};
        }
    } catch (Exception) {
        std::cout << "Invalid Input." << std::endl;
    }
    
    while (getline(std::cin, cmd)){
        if (cmd == "q") {
            break;
        } else if (cmd == "r") {
            
        }
    }
}