#include "GameManager.h"

#include <conio.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using std::cout;
using std::endl;
using std::string;

/**
 * Main execution of the game
 */
void GameManager::Run() {
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  // initialize the gameboard and snake
  Gameboard gb;
  Snake s(gb);

  // keep the game running as long as running is true
  while (running_) {
    // record starting time
    high_resolution_clock::time_point startTime = high_resolution_clock::now();

    // wins game if length>30
    if (s.GetLength() >= 30) {
      break;
    }

    // interpret the keyboard input when any key of the keyboard is pressed
    if (kbhit()) {
      int ch = getch();
      s.changeDirection(ch);
      if (ch == 'e') {
        debug_mode_ = !debug_mode_;
      } else if (ch == 'q') {
        break;
      }
    }

    // update the board and the snake, and then print it out
    running_ = Update(gb, s);
    PrintBoard(gb, s);
    ++frame_no_;

    // record ending time, and calculate the rendering time
    high_resolution_clock::time_point endTime = high_resolution_clock::now();
    auto render_time = duration_cast<milliseconds>(endTime - startTime).count();

    string str = "Snake length: " + std::to_string(s.GetLength()) + "\n";

    if (debug_mode_) {
      str += "\nFrame Number: " + std::to_string(frame_no_)
          + "\nFrame Number: " + std::to_string(render_time) + " ms\n";
    }

    cout << str;

    render_time = duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count();

    // wait 0.5 seconds
    std::this_thread::sleep_for(milliseconds(500 - render_time));
  }

  cout << "\t\t!!! Game over !!!" << endl;
  cout << "Press [ENTER] to exit..." << endl;
  std::cin.ignore();
}

/**
 * Prints the gameboard to the console
 *
 * @param gb Gameboard
 * @param s Snake
 */
void GameManager::PrintBoard(const Gameboard &gb, const Snake &s) const {
  // clear the screen before we print
  system("cls");

  for (int x = 0; x < kWidth; ++x) {
    string line_buffer = "";
    for (int y = 0; y < kHeight; ++y) {
      // retrieves the tile value, convert into the character, and add to buffer
      bool head = (x == s.GetHeadXPos()) && (y == s.GetHeadYPos());
      line_buffer += gb.GetMapValue(gb.GetValue(x, y), head);
    }
    // output the buffer for the current line
    cout << line_buffer << endl;
  }
}

/**
 * Updates the gameboard
 *
 * @param gb Gameboard
 * @param s Snake
 * @return True if the game should run in the next cycle
 */
bool GameManager::Update(Gameboard &gb, Snake &s) {
  int dx = 0, dy = 0;

  // calculate the snake's next step
  switch (s.GetDirection()) {
    case Directions::up:
      dx = -1;
      dy = 0;
      break;
    case Directions::right:
      dx = 0;
      dy = 1;
      break;
    case Directions::down:
      dx = 1;
      dy = 0;
      break;
    case Directions::left:
      dx = 0;
      dy = -1;
      break;
    default:
      // will not happen
      break;
  }

  // determine new head position
  int new_x = s.GetHeadXPos() + dx;
  int new_y = s.GetHeadYPos() + dy;

  bool running = true;

  // if snake's head will touch a food, increase its length and regen the food
  if (gb.GetValue(new_x, new_y) == GameboardChar::kFood) {
    s.IncreaseLength();
    gb.GenerateFood();
  } else if (gb.GetValue(new_x, new_y) != GameboardChar::kBlank) {
    // snake's head will crash into wall/itself
    running = false;
  }

  // move head to new location, and set the tile value to the snake's length
  // snake's head will always have the value s.length, subsequent bodies have
  // value = s.length - difference
  s.SetHeadPos(new_x, new_y);
  gb.SetValue(s.GetHeadXPos(), s.GetHeadYPos(), s.GetLength() + 1);

  // for tiles containing a snake part, reduce the tile value by 1
  for (int i = 0; i < kWidth; i++) {
    for (int j = 0; j < kHeight; j++) {
      if (gb.GetValue(i, j) > GameboardChar::kBlank) {
        gb.DecreaseValue(i, j);
      }
    }
  }

  return running;
}
