#pragma once
#include "stdafx.h"

class Gun {
private:
	sf::Vector2f position;
	int fireRate;
	float speed;
	bool health[10];
	sf::Sprite gunSprite;
	sf::Texture gunTexture;
public:
	Gun();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	int getFireRate();
	float getSpeed();
	bool getHealth(int itr);
	void setHealth(int itr, bool health);
	sf::Sprite getSprite();
	void movementCalc(float direction, float time);
};