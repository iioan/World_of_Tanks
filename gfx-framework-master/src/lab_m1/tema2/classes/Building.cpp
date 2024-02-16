#include "Building.h"
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

Building::Building(float x, float y, float z, float sX, float sY, float sZ, glm::vec3 color)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->sX = sX;
    this->sY = sY;
    this->sZ = sZ;
    this->color = color;
    this->center = glm::vec3(x, y, z);
    this->scale = glm::vec3(sX, sY, sZ);
    this->halfSide = 0.5f;
    this->newHalfSideX = halfSide * sX;
    this->newHalfSideZ = halfSide * sZ;

    this->diagonal = 2 * sqrt(pow((0.85f * newHalfSideX), 2) + pow((0.85f * newHalfSideZ), 2));

    this->modelMatrix = glm::mat4(1.f);
    this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(x, y, z));
    this->modelMatrix = glm::scale(modelMatrix, scale);
}

glm::vec3 Building::scaleSquareCorner(const glm::vec3& originalCorner, float sX, float sY, float sZ)
{
    return glm::vec3(originalCorner.x * sX, originalCorner.y * sY, originalCorner.z * sZ);
}

bool Building::isInside(float pointX, float pointY, float pointZ)
{
    // Calculam coordonatele minime si maxime ale cubului
    float minX = x - newHalfSideX;
    float maxX = x + newHalfSideX;
    float minY = y - newHalfSideX;
    float maxY = y + newHalfSideX;
    float minZ = z - newHalfSideZ;
    float maxZ = z + newHalfSideZ;

    // Verificam daca punctul se afla in interiorul cubului
    return (pointX >= minX && pointX <= maxX) && (pointY >= minY && pointY <= maxY) &&
        (pointZ >= minZ && pointZ <= maxZ);
}