#pragma once

#include "Gameboard.h"

enum Directions {
  up = 0,
  right = 1,
  down = 2,
  left = 3
};

class Snake {
 public:
  Snake(Gameboard gb) : head_x_pos_(kHeight / 2), head_y_pos_(kWidth / 2),
                        direction_(0), length_(3) {
    gb.SetValue(head_x_pos_, head_y_pos_, 1);
  }
  void changeDirection(int);

  // getters
  int GetHeadXPos() const { return head_x_pos_; }
  int GetHeadYPos() const { return head_y_pos_; }
  int GetDirection() const { return direction_; }
  int GetLength() const { return length_; }

  // setters
  void IncreaseLength() { ++length_; }
  void SetHeadPos(const int x, const int y) {
    head_x_pos_ = x;
    head_y_pos_ = y;
  }

 private:
  int head_x_pos_;   // X-coordinate of the snake head
  int head_y_pos_;   // Y-coordinate of the snake head
  int direction_;  // direction the snake is facing
  int length_;     // current length of the snake
};
