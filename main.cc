#include "floor.h"
#include "exception.h"
#include <iostream>
int main(){
    std::string cmd;
    std::vector<Floor> floors;
    Player *p;
    std::cout << "Please select your race (h, e, d, o) : ";

    try {
        std::cin >> cmd;
        if (cmd == "h" && cmd != "e" && cmd != "d" && cmd != "o") {
            throw Exception{};
        }
    } catch (Exception) {
        std::cout << "Invalid Input." << std::endl;
    }
    
    while (std::cin >> cmd){
        if (cmd == "q") {
            break;
        }
    }
}