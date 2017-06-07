#include "stdafx.h"
#include "Gun.h"

Gun::Gun() { // controlls the turrets start position and loads image
	position.x = 500;
	position.y = 690;
	fireRate = 10;
	speed = 10;
	for (int i = 0; i < 10; i++) {
		if (i < 3) health[i] = true;
		else health[i] = false;
	}
	if (!gunTexture.loadFromFile("Armageddon_Images/Turret.Png")) {
		std::cout << "Error, file Armageddon_Images/Turret.Png failed to load";
		abort();
	}
	gunSprite.setTexture(gunTexture);
	gunSprite.setScale(0.2f, 0.2f);
	gunSprite.setPosition((float)position.x, (float)position.y);
}

sf::Vector2f Gun::getPosition() { // get the guns position
	return position;
}

void Gun::setPosition(sf::Vector2f pos) { // set the guns position
	position = pos;
}

int Gun::getFireRate() { // compare position bullet - position gun to firerate
	return fireRate;
}

float Gun::getSpeed() { // get the speed of the gun
	return speed;
}

bool Gun::getHealth(int i) { // get the health of the gun
	return health[i];
}

void Gun::setHealth(int i, bool health) { // setting the health
	this->health[i] = health;
}

sf::Sprite Gun::getSprite() { // getting the turret image
	return gunSprite;
}

void Gun::movementCalc(float direction, float time) {
	//calculate gun movement

	gunSprite.move(direction * 500 * time, 0);
}