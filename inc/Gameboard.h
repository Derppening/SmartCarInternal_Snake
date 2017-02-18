#pragma once

#include <array>

constexpr int kWidth = 32;
constexpr int kHeight = 32;

enum GameboardChar {
  kBlank = 0,
  kWall = -1,
  kFood = -2
};

class Gameboard {
 public:
  Gameboard();
  void GenerateFood();
  void DecreaseValue(const int x, const int y) { --board_.at(x).at(y); }

  // getters
  char GetMapValue(const int, const bool) const;
  int GetValue(const int x, const int y) const { return board_.at(x).at(y); }

  // setters
  void SetValue(const int x, const int y, const int val) { board_.at(x).at(y) = val; }

 private:
  std::array<std::array<int, kHeight>, kWidth> board_{ GameboardChar::kBlank }; // 2D array containing tile values

  int GenRandomX();
  int GenRandomY();
};
