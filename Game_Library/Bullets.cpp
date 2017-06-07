#include "stdafx.h"
#include "Bullets.h"

Bullets::Bullets() {  // setting values for Bullet data and loading image
	speed = (float) .2;
	position = sf::Vector2f(-100,1);
	fired = false;
	direction = 0;
	if (!bulletTexture.loadFromFile("Armageddon_Images/Bullet.png")) {
		std::cout << "Error, File Armageddon_Images/Bullet.PNG failed to load";
		abort();
	}
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(0.07f, 0.07f);
	bulletSprite.setPosition((float)position.x, (float)position.y);
}

float Bullets::getSpeed() { // getting speed of bullet
	return speed;
}

sf::Vector2f Bullets::getPos() { // get the bullets position
	return position;
}

bool Bullets::getFired() { // is the bullet being used (fired)
	return fired;
}

void Bullets::setFired(bool fire) { // set the bullet to being fired
	fired = fire;
}

void Bullets::setDirection(float direct) { // detting the direction of the bullet ( left, right, or center)
	direction = direct;
}

sf::Sprite &Bullets::getSprite() { // getting the bullet sprite
	return bulletSprite;
}

void Bullets::movementCalc(float time) {
	//calculate movement of bullet
	
	bulletSprite.move(direction * 150 * time, -1000 * time);
}