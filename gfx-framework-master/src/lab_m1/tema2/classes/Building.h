#pragma once
#include <string>
#include "components/simple_scene.h"

class Building {
public:
	Building() {

	}
	Building::Building(float x, float y, float z, float sX, float sY, float sZ, glm::vec3 color);
	bool Building::isInside(float pointX, float pointY, float pointZ);
	glm::vec3 Building::scaleSquareCorner(const glm::vec3& originalCorner, float sX, float sY, float sZ);
	float x;
	float y;
	float z;
	float sX;
	float sY;
	float sZ;
	float halfSide;
	float newHalfSideX;
	float newHalfSideZ;
	float diagonal;

	glm::vec3 color;
	glm::mat4 modelMatrix;
	glm::vec3 center;
	glm::vec3 scale;
};