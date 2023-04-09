#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "cell.h"
#include "textdisplay.h"
#include <random>
#include "actiondisplay.h"
#include "position.h"

enum class Direction{ no, so, ea, we, ne, nw, se, sw };

class Floor{
    std::vector<std::vector<Cell>> theFloor;
    std::vector<Position> enemies;
    std::vector<Position> items;
    std::vector<Position> passages;
    std::vector<Position> doors;
    std::default_random_engine rng;
    TextDisplay* td;
    ActionDisplay* ad;
    Cell* stair;
    // ob *ob;
    Player* player;
    Position playerPos;
    int level;
    int suitLevel;
    int suitRandomGeneration();
    int itemNumberRandomGeneration();
    int chamberRandomGeneration(int shufflenumber);
    Position randomPosition(std::vector<Position>& chamber);
    CellType enemyRandomGeneration(int shufflenumber);
    int randomGenerationBasedOnProbability(std::vector<int> p);
public:
    Floor();
    std::default_random_engine getRng() const{ return rng; }
    void mapGenerator(std::string filename);
    std::vector<std::vector<Position>> chamberConstruction();
    void enemyAction();
    void playerMove(Position dir);
    void playerAttack(Position dir);
    void playerUse(Position dir);
    void goldnavigation();
    void suitnavigation();
    bool isOnStair();
    bool isWon();
    bool isLost();
    Player* getPlayer() const{ return player; }
    void init(Player*& player, int level, int suitLevel, std::default_random_engine rng);
    std::string navigation(Position dir);

    Position getPlayerPos(){ return playerPos; }
    friend std::ostream& operator<<(std::ostream& out, const Floor& f);
    ~Floor();
};

#endif
