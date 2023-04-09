#include "floor.h"
#include "exception.h"
#include "controller.h"
#include <iostream>

int main(int argc, char *argv[]){   
    Controller ctr;
    std::string cmd;
    std::cout << "Please select your race (h, e, d, o) : ";
    try {
        std::cin >> cmd;
        if (cmd == "h") {
            ctr.setPlayer
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

        } else {

        }
        if (ctr.Won()) {

        }
    }
}