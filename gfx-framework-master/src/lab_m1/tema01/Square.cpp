#include "Square.h"
#include <iostream>
#include <cmath>

Square::Square(int x, int y, int side, int line) {
	this->x = x;
	this->y = y;
	this->side = side;
	this->line = line;
	this->xMax = x + side;
	this->yMax = y + side;
	this->free = 0;
	this->underAttack = -1;
	this->lastAttack = 0;
}

// Verifica daca un punct este in interiorul patratului
bool Square::isInside(int x, int y) {
	if (x >= this->x && x <= this->xMax && y >= this->y && y <= this->yMax) {
		return true;
	}
	return false;
}

// Updateaza timpul de asteptare pentru atac
void Square::updateTime() {
	time_t currentTime = std::time(nullptr);
	double deltaTime = difftime(currentTime, this->lastAttack);
	this->lastAttack = currentTime;
	this->waitingTimeAttack += deltaTime;
}