#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Snake.h"
#include "Gameboard.h"

class GameManager {
public:
    bool running;
    void run();
    bool update(Gameboard&, Snake&);
private:
    void initBoard();
    void initSnake(Snake);
    void clearScreen();
    void printMap(Gameboard, Snake);
    char getMapValue(int, bool&);
};
#endif
