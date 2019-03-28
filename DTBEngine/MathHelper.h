#pragma once

#include "libs.h"

float GetDistance(sf::Vector2f v1, sf::Vector2f v2) // distance between vectors
{
	float x = v2.x - v1.x;
	float y = v2.y - v1.y;
	return (float) sqrt(x * x + y * y);
}

float GetDistance(float x1, float y1, float x2, float y2) // distance between vectors (over)
{
	return GetDistance(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2));
}

float GetDistance(sf::Vector2f vec) // distance detween points
{
	return (float) sqrt(vec.x * vec.x + vec.y * vec.y);
}

float GetDistance(float x, float y) // distance detween points (over)
{
	return (float)sqrt(x * x + y * y);
}