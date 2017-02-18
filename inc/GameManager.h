#pragma once

#include "Snake.h"
#include "Gameboard.h"

class GameManager {
 public:
  GameManager() : running_(true), frame_no_(0), debug_mode_(false) {};
  bool Update(Gameboard &, Snake &);
  void Run();
 private:
  void PrintBoard(const Gameboard &, const Snake &) const;

  bool debug_mode_;
  bool running_;
  int frame_no_;
};
