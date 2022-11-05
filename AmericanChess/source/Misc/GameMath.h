#pragma once
#include <cmath>
#include "SFML/Graphics.hpp"

#define PI 3.141592f

class GameMath {
public:
	// return radian units
	static float getAngle(sf::Vector2f firstPos, sf::Vector2f secondPos);
	static float getDistance(sf::Vector2f firstPos, sf::Vector2f secondPos);
	static float getHarmonicMotion(float length, float duration, float currentTime, float initialPhase = 0.5f);
	static sf::Vector2f getMovingEquation(sf::Vector2f firstPos, sf::Vector2f secondPos, float duration, float currentTime);
	//convert radian to degree
	static float radToDegree(float angle);
};
