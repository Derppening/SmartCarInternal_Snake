#include "Snake.h"

// Changes snake direction from input
void Snake::changeDirection(int key) {
    switch (key) {
        case 'w':  // up
            if (direction != Directions::down) {
                direction = Directions::up;
            }
            break;
        case 'd':  // right
            if (direction != Directions::left) {
                direction = Directions::right;
            }
            break;
        case 's':  // down
            if (direction != Directions::up) {
                direction = Directions::down;
            }
            break;
        case 'a':  // left
            if (direction != Directions::right) {
                direction = Directions::left;
            }
            break;
        default:
            // not handled
            break;
    }
}
