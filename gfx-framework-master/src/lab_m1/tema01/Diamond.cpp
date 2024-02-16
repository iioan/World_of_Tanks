#include "Diamond.h"
#include <iostream>
#include <cmath>
#include <string>

Diamond::Diamond(int x, int y, std::string color, int line, int square) {
	this->x = x;
	this->y = y;
	this->color = color;
	this->line = line;
	this->square = square;
	this->scaleX = 1;
	this->scaleY = 1;
}

// Face factorii de scalare sa devina din ce in ce mai mici;
// Mai intai acestia sunt initializati cu 1, iar daca rombul trebuie sa dispara,
// se vor micsora cu 1.5 * deltaTime, astfel se produce efectul de micsorare a rombului.
// Atunci cand rombul este foarte mic, acesta va fi sters din vectorul de romburi.
void Diamond::Minimize(float deltaTime) {
	if (this->scaleX < 1) {
		this->scaleX -= 1.5 * deltaTime;
		this->scaleY -= 1.5 * deltaTime;
	}
}

// Sterge stringul "Diamond" din numele culorii
std::string Diamond::removeDiamond() {
	std::string result = this->color;
	size_t pos = result.find("Diamond");
	if (pos != std::string::npos) {
		result.erase(pos, 7);
	}
	return result;
}

