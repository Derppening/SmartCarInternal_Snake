#include "Snake.h"

// Changes snake direction from input
void Snake::changeDirection(int key) {
  switch (key) {
    case 'w':  // up
      if (direction_ != Directions::down) {
        direction_ = Directions::up;
      }
      break;
    case 'd':  // right
      if (direction_ != Directions::left) {
        direction_ = Directions::right;
      }
      break;
    case 's':  // down
      if (direction_ != Directions::up) {
        direction_ = Directions::down;
      }
      break;
    case 'a':  // left
      if (direction_ != Directions::right) {
        direction_ = Directions::left;
      }
      break;
    default:
      // not handled
      break;
  }
}
