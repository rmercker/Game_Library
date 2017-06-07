#pragma once
#include "stdafx.h"
#include "Gun.h"

class Bullets {
private:
	float speed;
	sf::Vector2f position;
	bool fired;
	float direction;
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
public:
	Bullets();
	float getSpeed();
	sf::Vector2f getPos();
	bool getFired();
	void setFired(bool fire);
	void setDirection(float direct);
	sf::Sprite &getSprite();
	void movementCalc(float time);
};