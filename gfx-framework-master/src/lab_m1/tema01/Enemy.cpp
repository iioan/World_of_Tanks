#include "Enemy.h"
#include <iostream>
#include <cmath>
#include <string>

Enemy::Enemy(float x, float y, float length, int color, int line) {
	this->x = x;
	this->y = y;
	this->length = length;
	this->lives = 3;
	this->color = color;
	this->line = line;
	this->scaleX = 1;
	this->scaleY = 1;
	this->killed = 0;
}

// functie de update a lui x
// Daca acesta nu a fost omorat, se va misca la stanga
void Enemy::updateX(float deltaTimeSeconds) {
	if (this->killed == 0) {
		this->x -= 80 * deltaTimeSeconds;
	}
}

// Daca acesta a ajuns aproape de marginea din stanga a ecranului
// trebuie sa scadem numarul de vieti ai jucatorului
bool Enemy::stillInside() {
	if (this->x < 30) {
		return false;
	}
	return true;
}

// Face factorii de scalare sa devina din ce in ce mai mici;
// Mai intai acestia sunt initializati cu 1, iar daca hexagonul trebuie sa dispara,
// se vor micsora cu 1.5 * deltaTime, astfel se produce efectul de micsorare a inamicului.
// Atunci cand hexagonul este foarte mic, acesta va fi sters din vectorul de inamici.
void Enemy::Minimize(float deltaTimeSeconds) {
	if (this->scaleX < 1) {
		this->scaleX -= 1.5 * deltaTimeSeconds;
		this->scaleY -= 1.5 * deltaTimeSeconds;
	}
}

// Returneaza culoarea inamicului in functie de indexul sau
std::string Enemy::getType() {
	if (this->color == 0) {
		return "orange";
	}
	else if (this->color == 1) {
		return "blue";
	}
	else if (this->color == 2) {
		return "purple";
	}
	else if (this->color == 3) {
		return "yellow";
	}
}
