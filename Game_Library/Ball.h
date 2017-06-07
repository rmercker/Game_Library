#pragma once
#include "stdafx.h"

//Class responsible for creating and 
//keeping track of the ball.
class Ball {
	sf::Texture ballTexture[5];
	sf::Sprite ballSprite;
	sf::Vector2f direction;
	sf::Vector2f position;
	float speed;

public:
	Ball(sf::Vector2f position, sf::Vector2f dir, float sp);
	void reflectX();
	void reflectY();
	void setSpeed(float&);
	void setDirection(sf::Vector2f&);
	sf::Vector2u getSize() { return ballTexture[0].getSize(); };
	sf::Vector2f getPosition() { return ballSprite.getPosition(); };
	sf::Vector2f getDirection() { return direction; };
	float getSpeed() { return speed; };
	sf::Sprite sprite() { return ballSprite; };
	void update();
};