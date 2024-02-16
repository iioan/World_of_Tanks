// Player.h
#pragma once
#include <string>
#include "components/simple_scene.h"


class Player {
public:
    Player() {
        // Initialize member variables or perform other setup if needed
    }
    Player::Player(float x, float y, float z);
    bool Player::IsInside(glm::vec3 point);
    float x;
    float y;
    float z;
    glm::mat4 bodyModelMatrix;
    glm::mat4 turretModelMatrix;
    glm::vec3 tankCenter;
    float tankAngle;
    float turretAngle;
    float lungimeTun;
    float latimeTun;
    float radius;
    glm::vec3 tunCoordinates();
    int lives;
};