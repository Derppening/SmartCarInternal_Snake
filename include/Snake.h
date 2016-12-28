#pragma once
#include <iostream>

const int MAXLENGTH = 30;

class Snake {
public:
	bool LEFT, RIGHT, UP, DOWN;
	int length;
	char snake[MAXLENGTH];
	Snake() {
		LEFT = 0;
		RIGHT = 1;
		UP = 0;
		DOWN = 0;
		length = 1;
		snake[0] = 'G';
	}
	void eatfruit() {
		snake[length] = 'O';
		length++;
	}
};
