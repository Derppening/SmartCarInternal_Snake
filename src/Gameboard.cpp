#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Gameboard.h"

void Gameboard::init() {
	srand(time(NULL));

	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++)
			board[i][j] = 0;

	// Places top and bottom walls
	for (int x = 0; x < Width; ++x) {
		board[0][x] = -1;
		board[Width-1][x] = -1;
	}

	// Places left and right walls
	for (int y = 0; y < Height; y++) {
		board[y][0] = -1;
		board[y][Height-1] = -1;
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
		x = rand() % (Width - 2) + 1;
		y = rand() % (Height - 2) + 1;

		// If location is not free try again
	} while (board[x][y]);

	// Place new snakeLength
	board[x][y] = -2;
}
