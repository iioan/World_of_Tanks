#include "Player.h"
#include <cmath>
#include <iostream>
#include <string>

Player::Player(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->bodyModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
    this->turretModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
    this->tankAngle = 0.f;
    this->turretAngle = 0.f;
    this->tankCenter = glm::vec3(x, y, z);
    this->lungimeTun = 1.25f;
    this->latimeTun = 0.7f;
    this->lives = 5;
    this->radius = 0.85f;
}

glm::vec3 Player::tunCoordinates()
{
    glm::vec3 tunCenter = tankCenter;
    glm::vec3 tunCoordinates = tunCenter + glm::vec3(lungimeTun * sin((-1) * (turretAngle + tankAngle)), latimeTun,
        (-1) * lungimeTun * cos(turretAngle + tankAngle));
    return tunCoordinates;
}

bool Player::IsInside(glm::vec3 point)
{
    glm::vec3 thisCenter = glm::vec3(this->tankCenter);
    float thisRadius = this->radius;

    float distance =
        sqrt((thisCenter.x - point.x) * (thisCenter.x - point.x) + (thisCenter.z - point.z) * (thisCenter.z - point.z));

    return (distance < thisRadius);
}
