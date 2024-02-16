#pragma once
#include "Diamond.h"

/*
	Clasa se ocupa de patratul din joc
*/

class Square {
	public:
		Square::Square(int x, int y, int side, int line);
		bool Square::isInside(int x, int y);
		void Square::updateTime();
		int x;
		int y;
		int side;
		int xMax;  // coordonatele din dreapta sus ale patratului
		int yMax;
		int free;
		int line; // linia din care face parte patratul
		int underAttack; // -1, rombul nu este atacat; restul valorilor -> atac
		time_t lastAttack; // timpul ultimului atac
		float waitingTimeAttack; // timpul de asteptare intre atacuri
};