#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "cell.h"
#include "textdisplay.h"


class Floor{
    std::vector<std::vector<Cell>> theFloor;
    std::vector<Enemy> enemies;
    std::vector<Item> items;
    TextDisplay* td;
    Cell* stair;
    // ob *ob;
    Player* player;
    int level;
public:

    void move();
    bool isWon();
    bool isLost();
    void init(Player* player, int level);
    friend std::ostream& operator<<(std::ostream& out, const Floor& f);
};

#endif
