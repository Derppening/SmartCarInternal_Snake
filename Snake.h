/*
 * Snake.h
 *
 *  Created on: 2016¦~12¤ë28¤é
 *      Author: poon
 */

#ifndef SNAKE_H_
#define SNAKE_H_
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

#endif /* SNAKE_H_ */
