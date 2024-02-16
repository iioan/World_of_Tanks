// Villain.h
#pragma once
#include <string>
#include "components/simple_scene.h"
#include "Player.h"

enum class MovementState
{
    GoingForward,
    GoingBackward,
    InPlaceRotationLeft,
    InPlaceRotationRight
};


class Villain {
public:
    Villain() {
        // Initialize member variables or perform other setup if needed
    }
    Villain::Villain(float x, float y, float z, float firstRotation);
    void Villain::UpdateVillain(float deltaTime);
    bool Villain::IsInsideVillain(Villain villain);
    glm::vec3 tunCoordinates();
    bool Villain::IsInside(glm::vec3 point);
    void Villain::GenerateAttackPlayer(glm::vec3 player, float deltaTime);
    bool Villain::GetMissile(); 

    float x;
    float y;
    float z;
    float tankAngle;
    float turretAngle;
    float lungimeTun;
    float latimeTun;
    float radius;

    glm::mat4 bodyModelMatrix;
    glm::mat4 turretModelMatrix;
    glm::vec3 tankCenter;

    int lives;
    int waitingTime;

    bool killed;
    bool attack = false;

    time_t waiting;
    time_t attackTime;
    MovementState movementState;
};