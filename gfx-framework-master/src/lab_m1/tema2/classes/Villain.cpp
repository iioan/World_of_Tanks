#include "Villain.h"
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <string>

Villain::Villain(float x, float y, float z, float firstRotation)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->tankAngle = firstRotation;
    this->turretAngle = 0.f;
    this->tankCenter = glm::vec3(x, y, z);
    this->lungimeTun = 1.25f;
    this->latimeTun = 0.7f;
    this->lives = 4;
    this->radius = 0.85f;

    this->waitingTime = rand() % 5 + 2;
    this->waiting = time(NULL);
    this->movementState = MovementState::GoingForward;

    this->killed = false;
    this->attack = false;
    this->attackTime = time(NULL);
}

glm::vec3 Villain::tunCoordinates()
{
    glm::vec3 tunCenter = tankCenter;
    glm::vec3 tunCoordinates =
        tunCenter + glm::vec3(lungimeTun * sin((-1) * (turretAngle)), latimeTun, (-1) * lungimeTun * cos(turretAngle));
    return tunCoordinates;
}

int GetRandomNumberInRange(const int minInclusive, const int maxInclusive)
{
    static std::random_device randomDevice;
    static std::default_random_engine randomEngine(randomDevice());

    std::uniform_int_distribution<int> uniformDist(minInclusive, maxInclusive);

    return uniformDist(randomEngine);
}

MovementState GetNextMovementState(const MovementState currentState)
{
    int randomChange = GetRandomNumberInRange(0, 1);
    MovementState nextState = currentState;

    switch (currentState)
    {
    case MovementState::GoingForward:
    case MovementState::GoingBackward:
        nextState = (randomChange == 1) ? MovementState::InPlaceRotationLeft : MovementState::InPlaceRotationRight;
        break;

    case MovementState::InPlaceRotationLeft:
    case MovementState::InPlaceRotationRight:
        nextState = (randomChange == 1) ? MovementState::GoingForward : MovementState::GoingBackward;
        break;

    default:
        break;
    }

    return nextState;
}

std::string getMovementString(const MovementState movementState)
{
    std::map<MovementState, std::string> movementStateToStringMap = {
        {MovementState::GoingForward, "GoingForward"},
        {MovementState::GoingBackward, "GoingBackward"},
        {MovementState::InPlaceRotationLeft, "InPlaceRotationLeft"},
        {MovementState::InPlaceRotationRight, "InPlaceRotationRight"} };

    return movementStateToStringMap[movementState];
}

void Villain::UpdateVillain(float deltaTime)
{
    // Updateaza starile tancului alaturi de pozitii, unghiuri si timpul de asteptare
    time_t currentTime = time(NULL);
    if (currentTime - waiting >= waitingTime)
    {
        movementState = GetNextMovementState(movementState);
        waiting = currentTime;
        waitingTime = rand() % 5 + 4;
    }
    else
    {
        float forwardSpeed = 2.5f * deltaTime;
        switch (movementState)
        {
        case MovementState::GoingForward:
            if ((tankCenter.x < -36.f || tankCenter.x > 36.f || tankCenter.z < -36.f || tankCenter.z > 36.f))
            {
                this->tankCenter = this->tankCenter + forwardSpeed * glm::vec3(sin(tankAngle), 0, cos(tankAngle));
                this->movementState = MovementState::GoingBackward;
            }
            else
            {
                this->tankCenter =
                    this->tankCenter + forwardSpeed * glm::vec3(sin((-1) * tankAngle), 0, (-1) * cos(tankAngle));
            }
            break;

        case MovementState::GoingBackward:
            if ((tankCenter.x < -36.f || tankCenter.x > 36.f || tankCenter.z < -36.f || tankCenter.z > 36.f))
            {
                this->tankCenter = this->tankCenter - forwardSpeed * glm::vec3(sin(tankAngle), 0, cos(tankAngle));
                this->movementState = MovementState::GoingForward;
            }
            else
            {
                this->tankCenter =
                    this->tankCenter - forwardSpeed * glm::vec3(sin((-1) * tankAngle), 0, (-1) * cos(tankAngle));
            }
            break;
        case MovementState::InPlaceRotationLeft:
            this->tankAngle += deltaTime;
            break;
        case MovementState::InPlaceRotationRight:
            this->tankAngle -= deltaTime;
            break;
        }
    }
}

bool Villain::IsInsideVillain(Villain villain)
{
    glm::vec3 otherCenter = glm::vec3(villain.tankCenter);
    glm::vec3 thisCenter = glm::vec3(this->tankCenter);
    float otherRadius = villain.radius;
    float thisRadius = this->radius;

    float distance = sqrt((thisCenter.x - otherCenter.x) * (thisCenter.x - otherCenter.x) +
        (thisCenter.y - otherCenter.y) * (thisCenter.y - otherCenter.y) +
        (thisCenter.z - otherCenter.z) * (thisCenter.z - otherCenter.z));

    return (distance <= (thisRadius + otherRadius));
}

bool Villain::IsInside(glm::vec3 point)
{
    glm::vec3 thisCenter = glm::vec3(this->tankCenter);
    float thisRadius = this->radius * 1.5f;

    float distance =
        sqrt((thisCenter.x - point.x) * (thisCenter.x - point.x) + 
            (thisCenter.y - point.y) * (thisCenter.y - point.y) +
            (thisCenter.z - point.z) * (thisCenter.z - point.z));

    return (distance <= thisRadius);
}

void Villain::GenerateAttackPlayer(glm::vec3 player, float deltaTime)
{
    glm::vec3 enemyCenter = glm::vec3(this->tankCenter);

    float distance = glm::distance(enemyCenter, player);
    if (distance < 7.0f)
    {
        this->attack = true;
        // Aflu unghiul dintre pozitia playerului si pozitia tancului
        float theta = acos(glm::dot(glm::normalize(player - enemyCenter), glm::vec3(0, 0, 1)));

        if (player.x < enemyCenter.x)
        {
            theta = 2 * M_PI - theta;
        }

        // Updatam 'smoothly' unghiul turetei
        float rotationSpeed = 0.1f * deltaTime;
        this->turretAngle = glm::mix(this->turretAngle, static_cast<float>(theta - M_PI), rotationSpeed);
    }
    else
    {
        // Tranzitie catre unghiul initial a turetei
        this->attack = false;
        float rotationSpeed = 0.1f * deltaTime;
        this->turretAngle = glm::mix(this->turretAngle, this->tankAngle, rotationSpeed);
        this->attackTime = time(NULL);
    }
}

bool Villain::GetMissile()
{
    time_t currentTime = time(NULL);
    if (this->attack == true)
    {
        if (currentTime - this->attackTime >= 1.5f)
        {
            this->attackTime = currentTime;
            return true;
        }
    }
    return false;
}