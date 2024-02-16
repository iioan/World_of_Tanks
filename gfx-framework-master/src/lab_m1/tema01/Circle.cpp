#include "Circle.h"
#include <iostream>
#include <string>
#include <cmath>

Circle::Circle(float x, float y, int radius, std::string type) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->type = type;
	this->angularStep = 0;
	this->killed = 0;
}

// verifica daca punctul (x, y) se afla in interiorul cercului
int Circle::isInside(int x, int y) const {
	return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <=  radius * radius;
}

// updateaza pozitia si unghiul de rotatie al stelutei de atac
void Circle::Update(float deltaTime) {
	this->angularStep += 5 * deltaTime;
	this->x += 250 * deltaTime;
}

// verifica daca steaua a depasit rezolutia
bool Circle::stillInside() {
	if (this->x > 1280 + radius * 2) {
		return false;
	}
	return true;
}

// sterge sirul "Star" din numele stelutei
std::string Circle::removeStar() {
	if (this->type == "orangeStar") {
		return "orange";
	}
	else if (this->type == "blueStar") {
		return "blue";
	}
	else if (this->type == "purpleStar") {
		return "purple";
	}
	else if (this->type == "yellowStar") {
		return "yellow";
	}
}
