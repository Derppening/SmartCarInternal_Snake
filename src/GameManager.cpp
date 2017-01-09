#include "../include/GameManager.h"

#include <conio.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using std::cout;
using std::endl;

/**
 * Main execution of the game
 */
void GameManager::run() {
    using namespace std::chrono;

    // initialize the gameboard and snake
    Gameboard gb;
    Snake s(gb);

    // keep the game running as long as running is true
    while (running) {
        // record starting time
        high_resolution_clock::time_point startTime = high_resolution_clock::now();

        // wins game if length>30
        if (s.getLength() >= 30) {
            break;
        }

        // interpret the keyboard input when any key of the keyboard is pressed
        if (kbhit()) {
            int ch = getch();
            s.changeDirection(ch);
            if (ch == 'e') {
                debugMode = !debugMode;
            }
        }

        // update the board and the snake, and then print it out
        running = update(gb, s);
        printBoard(gb, s);
        ++frameNumber;

        // record ending time, and calculate the rendering time
        high_resolution_clock::time_point endTime = high_resolution_clock::now();
        auto renderTime = duration_cast<milliseconds>(endTime - startTime).count();

        cout << "Snake length: " << s.getLength() << endl;

        if (debugMode) {
            cout << endl << "Frame Number: " << frameNumber << endl;
            cout << "Frame Time: " << renderTime << " ms" << endl;
        }

        // wait 0.5 seconds
        std::this_thread::sleep_for(milliseconds(500-renderTime));
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
void GameManager::printBoard(Gameboard gb, Snake s) {
    // clear the screen before we print
    system("cls");

    for (int x = 0; x < kWidth; ++x) {
        std::string lineBuffer = "";
        for (int y = 0; y < kHeight; ++y) {
            // retrieves the tile value, convert into the character, and add to buffer
            bool head = (x == s.getHeadXPos()) && (y == s.getHeadYPos());
            lineBuffer += gb.getMapValue(gb.getValue(x, y), head);
        }
        // output the buffer for the current line
        cout << lineBuffer << endl;
    }
}

/**
 * Updates the gameboard
 *
 * @param gb Gameboard
 * @param s Snake
 * @return True if the game should run in the next cycle
 */
bool GameManager::update(Gameboard &gb, Snake &s) {
    int dx = 0, dy = 0;

    // calculate the snake's next step
    switch (s.getDirection()) {
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
    int newx = s.getHeadXPos() + dx;
    int newy = s.getHeadYPos() + dy;

    bool running = true;

    // if snake's head will touch a food, increase its length and regen the food
    if (gb.getValue(newx, newy) == GameboardChar::food) {
        s.increaseLength();
        gb.generateFood();
    } else if (gb.getValue(newx, newy) != GameboardChar::blank) {
        // snake's head will crash into wall/itself
        running = false;
    }

    // move head to new location, and set the tile value to the snake's length
    // snake's head will always have the value s.length, subsequent bodies have
    // value = s.length - difference
    s.setHeadPos(newx, newy);
    gb.setValue(s.getHeadXPos(), s.getHeadYPos(), s.getLength() + 1);

    // for tiles containing a snake part, reduce the tile value by 1
    for (int i = 0; i < kWidth; i++) {
        for (int j = 0; j < kHeight; j++) {
            if (gb.getValue(i, j) > GameboardChar::blank) {
                gb.decreaseValue(i, j);
            }
        }
    }

    return running;
}
