#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "cell.h"
#include "textdisplay.h"
#include "actiondisplay.h"


enum class Direction{ no, so, ea, we, ne, nw, se, sw };

class Floor{
    std::vector<std::vector<Cell>> theFloor;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    TextDisplay* td;
    ActionDisplay* ad;
    Cell* stair;
    // ob *ob;
    Player player;
    int level;
public:
    void mapGenerator(std::string filename);
    std::vector<std::vector<Position>> chamberConstruction();
    void enemyAction();
    void playerMove(Direction dir);
    void playerAttack();
    void playerUse();
    bool isOnStair();
    bool isLost();
    void init(Player& player, int level);
    friend std::ostream& operator<<(std::ostream& out, const Floor& f);
    ~Floor();
};

#endif
