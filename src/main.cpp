#include <iostream>
#include <conio.h>
#include <thread>

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(int key);
void clearScreen();
void generateFood();

char getMapValue(int value);

// Map dimensions
const int kMapWidth = 32;
const int kMapHeight = 32;

const int kMapSize = kMapWidth * kMapHeight;

// The tile values for the board
int board[kMapSize];

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 3;

// Determine if game is running
bool running;

int main() {
    run();
    return 0;
}

// Main game function
void run() {
    // Initialize the board
    initMap();
    running = true;
    while (running) {
        // If a key is pressed
        if (kbhit()) {
            // Change to direction determined by key pressed
            changeDirection(getch());
        }
        // Update the board
        update();

        // Clear the screen
        clearScreen();

        // Print the board
        printMap();

        // wait 0.5 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Print out game over text
    std::cout << "\t\t!!!Game over!" << std::endl << "\t\tYour score is: " << food;

    // Stop console from closing instantly
    std::cin.ignore();
}

// Changes snake direction from input
void changeDirection(int key) {
    /*
      W
    A + D
      S

      1
    4 + 2
      3
    */
    switch (key) {
        case 'w': // up
            if (direction != 2) direction = 0;
            break;
        case 'd': // right
            if (direction != 3) direction = 1;
            break;
        case 's': // down
            if (direction != 4) direction = 2;
            break;
        case 'a': // left
            if (direction != 5) direction = 3;
            break;
        default:
            // not handled
            break;
    }
}

// Moves snake head to new location
void move(int dx, int dy) {
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (board[newx + newy * kMapWidth] == -2) {
        // Increase food value (body length)
        food++;

        // Generate new food on board
        generateFood();
    }

        // Check location is free
    else if (board[newx + newy * kMapWidth] != 0) {
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    board[headxpos + headypos * kMapWidth] = food + 1;

}

// Clears screen
void clearScreen() {
    // Clear the screen
    system("cls");
}

// Generates new food on board
void generateFood() {
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the board
        x = rand() % (kMapWidth - 2) + 1;
        y = rand() % (kMapHeight - 2) + 1;

        // If location is not free try again
    } while (board[x + y * kMapWidth] != 0);

    // Place new food
    board[x + y * kMapWidth] = -2;
}

// Updates the board
void update() {
    // Move in direction indicated
    switch (direction) {
        case 0:
            move(-1, 0);
            break;
        case 1:
            move(0, 1);
            break;
        case 2:
            move(1, 0);
            break;
        case 3:
            move(0, -1);
            break;
    }

    // Reduce snake values on board by 1
    for (int i = 0; i < kMapSize; i++) {
        if (board[i] > 0) board[i]--;
    }
}

// Initializes board
void initMap() {
    // Places the initial head location in middle of board
    headxpos = kMapWidth / 2;
    headypos = kMapHeight / 2;
    board[headxpos + headypos * kMapWidth] = 1;

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

    // Generates first food
    generateFood();
}

// Prints the board to console
void printMap() {
    for (int x = 0; x < kMapWidth; ++x) {
        for (int y = 0; y < kMapHeight; ++y) {
            // Prints the value at current x,y location
            std::cout << getMapValue(board[x + y * kMapWidth]);
        }
        // Ends the line for next x value
        std::cout << std::endl;
    }
    std::cout << "\t\tSnake length: " << food << std::endl;
}

// Returns graphical character for display from board value
char getMapValue(int value) {
    // Returns a part of snake body
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
        case -1: return 'X';
            // Return food
        case -2: return 'O';
    }
}