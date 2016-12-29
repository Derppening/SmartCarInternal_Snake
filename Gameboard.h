#ifndef GAMBOARD_H_
#define GAMBOARD_H_
//dimensions
const int Width = 32;
const int Height = 32;

const int Size = Width * Height;

class Gameboard {
public:
    void init();
    void generateFood();

    // The tile values for the board
    int board[Width][Height];
};

#endif
