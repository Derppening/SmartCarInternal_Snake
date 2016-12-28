#pragma once

// Map dimensions
const int kMapWidth = 32;
const int kMapHeight = 32;

const int kMapSize = kMapWidth * kMapHeight;

class Gameboard {
public:
    void init();
    void generateFood();

    // The tile values for the board
    int board[kMapSize];
};