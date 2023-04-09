#include "floor.h"
#include "exception.h"
#include "controller.h"
#include <iostream>

int main(int argc, char* argv[]){
    Controller ctr;
    std::string cmd;
    std::cout << "Please select your race (h, e, d, o) or quit (q) : ";
    try{
        std::cin >> cmd;
        if (cmd != "h" && cmd != "e" && cmd != "d" && cmd != "o" && cmd != "q"){
            throw Exception{};
        } else if (cmd == "q"){
            return 0;
        } else{
            ctr.initMap(cmd);
        }
    }
    catch (Exception){
        std::cout << "Invalid Input" << std::endl;
    }

    while (std::cin >> cmd){
        if (cmd == "q"){
            break;
        } else if (cmd == "r"){
            std::cout << "\nPlease select your race (h, e, d, o) or quit (q) : ";
            try{
                std::cin >> cmd;
                if (cmd != "h" && cmd != "e" && cmd != "d" && cmd != "o"){
                    throw Exception{};
                } else{
                    ctr.restart(cmd);
                }
            }
            catch (Exception){
                std::cout << "Invalid Input" << std::endl;
            }
        } else if (cmd == "a"){
            std::cin >> cmd;
            ctr.playerAttack(cmd);
        } else if (cmd == "u"){
            std::cin >> cmd;
            ctr.useItem(cmd);
        } else if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" ||
            cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw"){
            ctr.playerMove(cmd);
        }
    }
}
