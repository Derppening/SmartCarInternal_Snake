#include <iostream>
#include <ctime>

#include "Gameboard.h"

void Gameboard::init() {
    srand(time(NULL));

    for (int x = 0; x < kMapSize; x++) {
        board[x] = 0;
    }

    // Places top and bottom walls
    for (int x = 0; x < kMapWidth; ++x) {
        board[x] = -1;
        board[x + (kMapHeight - 1) * kMapWidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < kMapHeight; y++) {
        board[0 + y * kMapWidth] = -1;
        board[(kMapWidth - 1) + y * kMapWidth] = -1;
    }

    // Generates first length
    generateFood();
}

// Generates new snakeLength on board
void Gameboard::generateFood() {
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the board
        x = rand() % (kMapWidth - 2) + 1;
        y = rand() % (kMapHeight - 2) + 1;

        // If location is not free try again
    } while (board[x + y * kMapWidth] != 0);

    // Place new snakeLength
    board[x + y * kMapWidth] = -2;
}