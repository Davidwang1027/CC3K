#ifndef ELF_H
#define ELF_H

#include "player.h"

class Elf : public Player{
    public:
    Elf() : Player("Elf", 140, 140, 30, 10, 0){};
};

#endif
