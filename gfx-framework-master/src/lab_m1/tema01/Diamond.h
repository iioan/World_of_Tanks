#pragma once
#include <string>

/*
	Clasa care reprezinta un romb;
*/

class Diamond {
public:
	Diamond::Diamond(int x, int y, std::string color, int line, int square);
	void Diamond::Minimize(float deltaTimeSeconds);
	std::string Diamond::removeDiamond();
	int x;
	int y;
	int line; // linia pe care se afla rombul (dupa drag n drop)
	std::string color;
	float scaleX;
	float scaleY;
	int square; // indexul patratului de joc pe care se afla rombul

};