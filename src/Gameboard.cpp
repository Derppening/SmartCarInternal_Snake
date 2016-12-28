#include <iostream>
#include <string>

#include "Gameboard.h"

void Gameboard::outputBoard() {
    for (int i = 0; i < kCol; i++) {
        std::string s;
        for (int j = 0; j < kRow; j++) {
            s += board[i][j];
        }
        std::cout << s << std::endl;
    }
}

Gameboard::Gameboard() {
    for (int i = 0; i < kRow*kCol; i++) {
        board[i/128][i%128] = ' ';
    }

    for (int i = 0; i < 128; i++) {
        board[0][i] = '-';
        board[127][i] = '-';
        board[i][0] = '|';
        board[i][127] = '|';
    }
}

Gameboard::setChar(char ch, int row, int col) {
    board[row][col] = ch;
}