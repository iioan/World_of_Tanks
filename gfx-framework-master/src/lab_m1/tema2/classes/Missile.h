// Missile.h
#pragma once
#include <string>
#include "components/simple_scene.h"

class Missile {
public:
	Missile() {
	
	}
	Missile::Missile(float x, float y, float z, float turretAngle, float bodyAngle);
	float x;
	float y;
	float z;
	float turretAngle;
	float bodyAngle;
	glm::mat4 modelMatrix;
	glm::vec3 center;
	glm::vec3 scale;
	void Missile::Update();
	bool expired;
};