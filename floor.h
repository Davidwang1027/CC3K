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
#include "position.h"

enum class Direction{ no, so, ea, we, ne, nw, se, sw };

class Floor{
    std::vector<std::vector<Cell>> theFloor;
    std::vector<Position> enemies;
    std::vector<Position> items;
    std::vector<Position> passages;
    std::vector<Position> doors;
    TextDisplay* td;
    ActionDisplay* ad;
    Cell* stair;
    // ob *ob;
    Player* player;
    Position playerPos;
    int level;
    int suitLevel;
public:
    void mapGenerator(std::string filename);
    std::vector<std::vector<Position>> chamberConstruction();
    void enemyAction();
    void playerMove(Position dir);
    void playerAttack(Position dir);
    void playerUse(Position dir);
    bool isOnStair();
    void init(Player*& player, int level, int suitLevel);
    std::string Floor::navigation(Position dir);
    friend std::ostream& operator<<(std::ostream& out, const Floor& f);
    ~Floor();
};

#endif
