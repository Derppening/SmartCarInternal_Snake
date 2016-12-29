#include <conio.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include "GameManager.h"

using std::cout;
using std::endl;

/**
 * Main execution of the game
 */
void GameManager::run() {

	// declare the gameboard and snake
	Gameboard gb;
	Snake s;

	// Initialize the board and snake
	gb.init();
	s.init(gb);

	// initialize timer clocks
	running = true;

	// keep the game running as long as running is true
	while (running) {
		// record starting time
		clock_t startTime = clock();

		// wins game if length>30
		if (s.length >= 30)
			break;

		// If a key is pressed
		if (kbhit()) {
			// Change to direction determined by key pressed
			s.changeDirection(getch());
		}

		// Update the board
		running = update(gb, s);

		// Clear the screen
		cout << "Clear Screen" << endl;
		clearScreen();

		// Print the board
		printMap(gb, s);

		// record ending time
		clock_t endTime = clock();

		double duration = (endTime - startTime);
		// wait 0.5 seconds
		Sleep(500 - duration);
	}

	// Print out game over text
	cout << "\t\t!!! Game over !!!" << endl << "\t\tYour score is: " << s.length
			<< endl;
	cout << "Press [ENTER] to continue..." << endl;

	// Stop console from closing instantly
	std::cin.ignore();
}

// Clears screen
void GameManager::clearScreen() {
	// Clear the screen
	system("cls");
}

// Prints the board to console
void GameManager::printMap(const Gameboard gb, const Snake s) {
	for (int x = 0; x < Width; ++x) {
		for (int y = 0; y < Height; ++y) {
			// Prints the value at current x,y location
			bool head = ((x == s.headxpos) && (y == s.headypos));
			cout << getMapValue(gb.board[x][y], head);
		}
		// Ends the line for next x value
		cout << endl;
	}
	cout << "\t\tSnake length: " << s.length << endl;
}

// Returns graphical character for display from board value
char GameManager::getMapValue(int value, bool& head) {
	// Returns a part of snake body
	if (value > 0) {
		if (head) {
			return 'X';
		}
		if (!head)
			return 'o';
	}

	switch (value) {
	// Return wall
	case -1:
		return 'F';
		// Return length
	case -2:
		return '$';
	default:
		return ' ';
	}
}

// Updates the game field
bool GameManager::update(Gameboard &gb, Snake &s) {
	int dx = 0, dy = 0;
	bool running = true;

	// Move in direction indicated
	switch (s.direction) {
	case 0:
		dx = -1;
		dy = 0;
		break;
	case 1:
		dx = 0;
		dy = 1;
		break;
	case 2:
		dx = 1;
		dy = 0;
		break;
	case 3:
		dx = 0;
		dy = -1;
		break;
	default:
		// will not happen
		break;
	}

	// determine new head position
	int newx = s.headxpos + dx;
	int newy = s.headypos + dy;

	// Check if there is length at location
	if (gb.board[newx][newy] == -2) {
		// Increase length value (body length)
		s.length++;

		// Generate new length on board
		gb.generateFood();
	} else if (gb.board[newx][newy] != 0) {
		// Check location is free
		running = false;
	}

	// Move head to new location
	s.headxpos = newx;
	s.headypos = newy;
	gb.board[s.headxpos][s.headypos] = s.length + 1;

	// Reduce snake values on board by 1
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Height; j++) {
			if (gb.board[i][j] > 0)
				gb.board[i][j]--;
		}

	return running;
}
