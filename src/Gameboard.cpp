#include "Gameboard.h"

#include <functional>
#include <random>
#include <chrono>

// RNG for generating food locations
std::default_random_engine re;
std::uniform_int_distribution<int> uid_x(0, kHeight - 2);
std::uniform_int_distribution<int> uid_y(0, kWidth - 2);

/**
 * Default constructor for Gameboard
 *
 * Resets randomizer, initializes board[][], and generates food
 */
Gameboard::Gameboard() {
    // sets seed of random engine using current time
    re.seed((unsigned)std::chrono::system_clock::now().time_since_epoch().count());

    // reset the array
    for (int i = 0; i < kWidth; ++i) {
        for (int j = 0; j < kHeight; ++j) {
            board[i][j] = GameboardChar::blank;
        }
    }

    // place top/bottom walls
    for (int x = 0; x < kHeight; ++x) {
        board[x][0] = GameboardChar::wall;
        board[x][kHeight-1] = GameboardChar::wall;
    }

    // place left/right walls
    for (int y = 0; y < kWidth; ++y) {
        board[0][y] = GameboardChar::wall;
        board[kWidth-1][y] = GameboardChar::wall;
    }

    // generate first food
    generateFood();
}

/**
 * Generates a piece of food on the map
 */
void Gameboard::generateFood() {
    int x = 0;
    int y = 0;

    // randomize the x,y-coordinates until it is valid (i.e. board[x][y] == 0)
    do {
        x = genRandomX() + 1;
        y = genRandomY() + 1;
    } while (board[x][y]);

    // set coords to be food
    board[x][y] = GameboardChar::food;
}

/**
 * Returns graphical character for display from board value
 *
 * @param value Value in the Gameboard array
 * @param head True if the tile is a head
 * @return Character displayed in console
 */
char Gameboard::getMapValue(int value, bool head) {
    if (value > 0) {
        return head ? 'X' : 'o';
    }

    switch (value) {
        case GameboardChar::wall:
            return 'F';
        case GameboardChar::food:
            return '$';
        default:
            return ' ';
    }
}

/**
 * Generates a random value based on the board height
 *
 * @return Random integer [0,kHeight-2]
 */
int Gameboard::genRandomX() {
    return uid_x(re);
}

/**
 * Generates a random value based on the board width
 *
 * @return Random integer [0,kWidth-2]
 */
int Gameboard::genRandomY() {
    return uid_y(re);
}
