#include "stdafx.h"
#include "Ball.h"

//Default constructor for Ball.
//pos is the starting position.
//dir is a 2D vector that controls the initial
//direction of the ball.
//sp is the initial speed of the ball.
Ball::Ball(sf::Vector2f pos, sf::Vector2f dir, float sp) {
	direction = dir;
	speed = sp;
	position = pos;
	ballTexture[0].loadFromFile("Ping_Images/BALL1.png");
	ballTexture[1].loadFromFile("Ping_Images/BALL2 nose.png");
	ballTexture[2].loadFromFile("Ping_Images/eyebrow.png");
	ballTexture[3].loadFromFile("Ping_Images/it is wednesday my bois.png");
	ballTexture[4].loadFromFile("Ping_Images/stoic.png");
	ballSprite.setTexture(ballTexture[0]);
	ballSprite.setPosition(position);
}

//Multiplies the x-component of direction by -1
//to reverse the ball's direction horizontally
void Ball::reflectX() {
	direction = sf::Vector2f(-direction.x, direction.y);
	int randSprite = rand() % 5;
	ballSprite.setTexture(ballTexture[randSprite]);
}

//Multiplies the y-component of direction by -1
//to reverse the ball's direction vertically.
void Ball::reflectY() {
	direction = sf::Vector2f(direction.x, -direction.y);
}

//Sets the speed of the ball.
void Ball::setSpeed(float &sp) {
	speed = sp;
}

void Ball::setDirection(sf::Vector2f &dir) {
	direction = dir;
}

//Meant to be used once per frame to update the ball's
//position based on its direction and speed.
void Ball::update() {
	ballSprite.setPosition(ballSprite.getPosition() + direction * speed);
}
