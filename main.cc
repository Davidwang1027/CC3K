#include "floor.h"
#include "exception.h"
#include "controller.h"
#include <iostream>


int restartGame(Controller& ctr, std::string filename){
    std::string cmd;
    std::cout << "Please select your race (h, e, d, o) or quit (q) : ";

    std::cin >> cmd;
    while (true){
        if (cmd != "h" && cmd != "e" && cmd != "d" && cmd != "o" && cmd != "q"){
            throw Exception{};
        } else if (cmd == "q"){
            return 0;
        } else{
            if (filename != "")
                ctr.restart(cmd, filename);
            else{
                ctr.restart(cmd);
            }
            return 1;
        }
    }
}

int main(int argc, char* argv[]){
    std::string filename = "";
    if (argc > 1){
        filename = argv[1];
    }
    Controller ctr;
    std::string cmd;
    std::cout << "Please select your race (h, e, d, o) or quit (q) : ";

    while (true){
        try{
            std::cin >> cmd;
            if (cmd != "h" && cmd != "e" && cmd != "d" && cmd != "o" && cmd != "q"){
                throw Exception{};
            } else if (cmd == "q"){
                return 0;
            } else{
                if (filename != ""){
                    ctr.initMap(cmd, filename);
                } else{
                    ctr.initMap(cmd);
                }
                break;
            }
        }
        catch (Exception){
            std::cout << "Invalid Input" << std::endl;
        }
    }
    while (true){
        try{
            while (std::cin >> cmd){
                if (cmd == "q"){
                    return 0;
                } else if (cmd == "r"){
                    restartGame(ctr, filename);
                } else if (cmd == "a"){
                    std::cin >> cmd;
                    ctr.playerAttack(cmd);
                    if (ctr.getIsLost()){
                        std::cout << "You lost!" << std::endl;
                        if (!restartGame(ctr, filename)){
                            return 0;
                        }
                    }
                } else if (cmd == "u"){
                    std::cin >> cmd;
                    ctr.useItem(cmd);
                    if (ctr.getIsLost()){
                        std::cout << "You lost!" << std::endl;
                        if (!restartGame(ctr, filename)){
                            return 0;
                        }
                    }
                } else if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" ||
                    cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw"){
                    ctr.playerMove(cmd);
                    if (ctr.getIsLost()){
                        std::cout << "You lost!" << std::endl;
                        if (!restartGame(ctr, filename)){
                            return 0;
                        }
                    }
                    if (ctr.getIsWon()){
                        std::cout << "Play again? (y/n) : " << std::endl;
                        std::cin >> cmd;
                        if (cmd == "y"){
                            if (!restartGame(ctr, filename)){
                                return 0;
                            }
                        } else{
                            return 0;
                        }
                    }
                } else{
                    throw Exception{};
                }
            }
        }
        catch (Exception){
            std::cout << "Invalid Input" << std::endl;
        }
    }
}
