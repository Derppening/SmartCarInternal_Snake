#pragma once

#include "Gameboard.h"

enum Directions {
    up = 0,
    right = 1,
    down = 2,
    left = 3
};

class Snake {
 private:
    int headxpos;   // X-coordinate of the snake head
    int headypos;   // Y-coordinate of the snake head
    int direction;  // direction the snake is facing
    int length;     // current length of the snake
 public:
    Snake(Gameboard gb) : headxpos(kHeight/2), headypos(kWidth/2),
            direction(0), length(3) {
        gb.setValue(headxpos, headypos, 1);
    }
    void changeDirection(int);

    // getters
    int getHeadXPos() { return headxpos; }
    int getHeadYPos() { return headypos; }
    int getDirection() { return direction; }
    int getLength() { return length; }

    // setters
    void increaseLength() { length++; }
    void setHeadPos(int x, int y) {
        headxpos = x;
        headypos = y;
    }
};
