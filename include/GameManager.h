#pragma once

#include "Snake.h"
#include "Gameboard.h"

class GameManager {
 private:
    bool debugMode;
    bool running;
    int frameNumber;

    void printBoard(Gameboard, Snake);
 public:
    GameManager() : running(true), frameNumber(0) {}
    bool update(Gameboard &, Snake &);
    void run();
};
