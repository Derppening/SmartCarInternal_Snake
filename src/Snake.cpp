#include "Snake.h"

void Snake::init(Gameboard gb) {
    // Places the initial head location in middle of board
    headxpos = 16;
    headypos = 16;
    direction = 0;
    length = 1;
    gb.board[headxpos][headypos] = 1;
}

// Changes snake direction from input
void Snake::changeDirection(int key) {
    switch (key) {
        case 'w': // up
            if (direction != 2) direction = 0;
            break;
        case 'd': // right
            if (direction != 3) direction = 1;
            break;
        case 's': // down
            if (direction != 4) direction = 2;
            break;
        case 'a': // left
            if (direction != 5) direction = 3;
            break;
        default:
            // not handled
            break;
    }
}
