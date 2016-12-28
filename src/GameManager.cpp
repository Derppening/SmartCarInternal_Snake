#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>

#include "GameManager.h"

using std::cout;
using std::endl;

/**
 * Main execution of the game
 */
void GameManager::run() {
    using namespace std::chrono;

    // declare the gameboard and snake
    Gameboard gb;
    Snake s;

    // Initialize the board and snake
    gb.init();
    s.init(gb);

    // initialize timer clocks
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point endTime;
    running = true;

    // keep the game running as long as running is true
    while (running) {
        // record starting time
        startTime = high_resolution_clock::now();

        // wins game if length>30
        if (s.length >= 30) break;

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
        printMap(gb, s.length);

        // record ending time
        endTime = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>( endTime - startTime ).count();

        // wait 0.5 seconds
        std::this_thread::sleep_for(milliseconds(500-duration));
    }

    // Print out game over text
    cout << "\t\t!!!Game over!" << endl << "\t\tYour score is: " << s.length << endl;
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
void GameManager::printMap(const Gameboard gb, const int length) {
    for (int x = 0; x < kMapWidth; ++x) {
        for (int y = 0; y < kMapHeight; ++y) {
            // Prints the value at current x,y location
            cout << getMapValue(gb.board[x + y * kMapWidth]);
        }
        // Ends the line for next x value
        cout << endl;
    }
    cout << "\t\tSnake length: " << length << endl;
}

// Returns graphical character for display from board value
char GameManager::getMapValue(int value) {
    // Returns a part of snake body
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
        case -1: return 'X';
            // Return length
        case -2: return 'O';
        default: return ' ';
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
    if (gb.board[newx + newy * kMapWidth] == -2) {
        // Increase length value (body length)
        s.length++;

        // Generate new length on board
        gb.generateFood();
    } else if (gb.board[newx + newy * kMapWidth] != 0) {
        // Check location is free
        running = false;
    }

    // Move head to new location
    s.headxpos = newx;
    s.headypos = newy;
    gb.board[s.headxpos + s.headypos * kMapWidth] = s.length + 1;

    // Reduce snake values on board by 1
    for (int i = 0; i < kMapSize; i++) {
        if (gb.board[i] > 0) gb.board[i]--;
    }

    return running;
}
