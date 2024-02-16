#include "Missile.h"
#include <cmath>
#include <iostream>
#include <string>

Missile::Missile(float x, float y, float z, float turretAngle, float bodyAngle)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->turretAngle = turretAngle;
    this->bodyAngle = bodyAngle;
    this->modelMatrix = glm::mat4(1.f);
    this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(x, y, z));
    this->modelMatrix = glm::scale(modelMatrix, scale);
    this->center = glm::vec3(x, y, z);
    this->scale = glm::vec3(0.20f);
    this->expired = false;
}

void Missile::Update()
{
    this->center = this->center + glm::vec3(0.04f * sin((-1) * (turretAngle + bodyAngle)), 0,
        (-1) * 0.04f * cos(turretAngle + bodyAngle));
    modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::translate(modelMatrix, center);
    modelMatrix = glm::scale(modelMatrix, scale);
}
