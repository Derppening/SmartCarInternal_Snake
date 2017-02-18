#include "Gameboard.h"

#include <chrono>
#include <functional>
#include <random>

// RNG for generating food locations
std::mt19937_64 gen;
std::uniform_int_distribution<int> uid_x(0, kHeight - 2);
std::uniform_int_distribution<int> uid_y(0, kWidth - 2);

/**
 * Default constructor for Gameboard
 *
 * Resets randomizer, initializes board[][], and generates food
 */
Gameboard::Gameboard() {
  // sets seed of random engine using current time
  gen.seed(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

  // place top/bottom walls
  for (int x = 0; x < kHeight; ++x) {
    board_.at(x).at(0) = GameboardChar::kWall;
    board_.at(x).at(kHeight - 1) = GameboardChar::kWall;
  }

  // place left/right walls
  for (int y = 0; y < kWidth; ++y) {
    board_.at(0).at(y) = GameboardChar::kWall;
    board_.at(kWidth - 1).at(y) = GameboardChar::kWall;
  }

  // generate first food
  GenerateFood();
}

/**
 * Generates a piece of food on the map
 */
void Gameboard::GenerateFood() {
  int x = 0;
  int y = 0;

  // randomize the x,y-coordinates until it is valid (i.e. board[x][y] == 0)
  do {
    x = GenRandomX() + 1;
    y = GenRandomY() + 1;
  } while (board_.at(x).at(y));

  // set coords to be food
  board_.at(x).at(y) = GameboardChar::kFood;
}

/**
 * Returns graphical character for display from board value
 *
 * @param value Value in the Gameboard array
 * @param head True if the tile is a head
 * @return Character displayed in console
 */
char Gameboard::GetMapValue(const int value, const bool head) const {
  if (value > 0) {
    return head ? 'X' : 'o';
  }

  switch (value) {
    case GameboardChar::kWall:return 'F';
    case GameboardChar::kFood:return '$';
    default:return ' ';
  }
}

/**
 * Generates a random value based on the board height
 *
 * @return Random integer [0,kHeight-2]
 */
int Gameboard::GenRandomX() {
  return uid_x(gen);
}

/**
 * Generates a random value based on the board width
 *
 * @return Random integer [0,kWidth-2]
 */
int Gameboard::GenRandomY() {
  return uid_y(gen);
}
