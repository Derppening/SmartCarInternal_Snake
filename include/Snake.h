#pragma once
#include <iostream>

const int MAXLENGTH = 30;

class Snake {
public:
	bool LEFT, RIGHT, UP, DOWN;
	int length;
	char snake[MAXLENGTH];
    Snake();
	void eatfruit() {
		snake[length] = 'O';
		length++;
	}
};
