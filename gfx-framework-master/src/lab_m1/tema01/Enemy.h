#pragma once 

#include <string>

class Enemy {
	public:
		Enemy::Enemy(float x, float y, float length, int color, int line);
		void Enemy::updateX(float deltaTimeSeconds);
		void Enemy::Minimize(float deltaTimeSeconds);
		std::string Enemy::getType();
		bool Enemy::stillInside();
		float x;
		float y; 
		int lives;
		int color;
		float length;
		float scaleX;
		float scaleY;
		int line;
		int killed;
};