#pragma once

#include "Gameboard.h"

class Snake {
public:
    void init(Gameboard);
    bool move(Gameboard&);
    void changeDirection(int);

    // Snake head details
    int headxpos;
    int headypos;
    int direction;

    // Amount of length the snake has (How long the body is)
    int length = 1;
};