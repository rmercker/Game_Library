#include "stdafx.h"
#include "Rock.h"

Rock::Rock() {
	// Loading all image files and aborting if fails to prevent errors
	if (!texture.loadFromFile("Armageddon_Images/250px-Meteorite.png")) {
		std::cout << "Error, file Images/Meteorite.Png failed to load";
		abort();
	}
	if (!destroy_text[1].loadFromFile("Armageddon_Images/meteorite_bottom_left.png")) {
		abort();
	}
	destroy[1].setTexture(destroy_text[1]);
	if (!destroy_text[0].loadFromFile("Armageddon_Images/meteorite_bottom_right.png")) {
		abort();
	}
	destroy[0].setTexture(destroy_text[0]);
	if (!destroy_text[3].loadFromFile("Armageddon_Images/meteorite_top_left.png")) {
		abort();
	}
	destroy[3].setTexture(destroy_text[3]);
	if (!destroy_text[2].loadFromFile("Armageddon_Images/meteorite_top_right.png")) {
		abort();
	}
	destroy[2].setTexture(destroy_text[2]);
	// end initiation of images

	//setting up boolean  and destruction images for rocks
	hit = false;
	drop = false;
	endImage = false;

	size = 1;
	speed = 1;
	horizPosition = (float) (rand() % 1000);

	destroy[1].setPosition(horizPosition + 70, -300 + 100);
	destroy[0].setPosition(horizPosition + 120, -300 + 100);
	destroy[3].setPosition(horizPosition + 70, -300 + 30);
	destroy[2].setPosition(horizPosition + 120, -300 + 30);

	destroy[1].scale(0.5, 0.5);
	destroy[0].scale(0.5, 0.5);
	destroy[3].scale(0.5, 0.5);
	destroy[2].scale(0.5, 0.5);

	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 0));
	sprite.scale(sf::Vector2f(0.5f, 0.5f));
	sprite.setPosition(sf::Vector2f( horizPosition, -300.0f));
}

void Rock::setSpeed(float speed) { //speed of rock
	this->speed = speed;
}

void Rock::setPosition(float time) { //moving rock
	sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 0.2f * time);
}

void Rock::setSize(float size) { // changing size of rock
	this->size = size;
}

void Rock::setHit(bool val) { // rock is destroyed
	hit = val;
}

void Rock::setDrop(bool val) { // rock is droping
	drop = val;
}

void Rock::setEndImage(bool val) { // stop showing destruction of rock image
	endImage = val;
}

bool Rock::getHit() { // is rock shot or hits ground
	return hit;
}

bool Rock::getDrop() { // drop rock boolean
	return drop;
}