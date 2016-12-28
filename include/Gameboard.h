#pragma once
#include <iostream>
#include <memory>

const int kRow = 128;
const int kCol = 128;

class Gameboard {
private:
    char board[kRow][kCol];
public:
    Gameboard();
    void outputBoard();
    void setChar(char, int, int);
};