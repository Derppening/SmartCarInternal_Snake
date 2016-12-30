#pragma once

const int kWidth = 32;
const int kHeight = 32;

enum GameboardChar {
    blank = 0,
    wall = -1,
    food = -2
};

class Gameboard {
 private:
    int board[kWidth][kHeight];  // 2D array containing tile values

    int genRandomX();
    int genRandomY();
 public:
    Gameboard();
    void generateFood();
    void decreaseValue(int x, int y) { --board[x][y]; }

    char getMapValue(int, bool);
    int getValue(int x, int y) { return board[x][y]; }

    void setValue(int x, int y, int val) { board[x][y] = val; }
};
