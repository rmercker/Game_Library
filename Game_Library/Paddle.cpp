#include "stdafx.h"
#include "Paddle.h"

//Default constructor of the paddle class.
Paddle::Paddle(sf::Vector2f spritePosition, sf::String str) {
	paddleTexture.loadFromFile(str);
	paddleSprite.setTexture(paddleTexture);
	paddleSprite.setPosition(spritePosition);
}

//Moves the paddle with a character input.
//Acceptable input is 'u' 'd' 
//for corresponding directions.
void Paddle::move(char direction) {

	switch (direction) {
	case 'u':
		paddleSprite.move(sf::Vector2f(0, -0.8f));
		break;
	case 'd':
		paddleSprite.move(sf::Vector2f(0, 0.8f));
		break;
	default:
		break;
	}

}

void Paddle::setPosition(sf::Vector2f &pos) {
	paddleSprite.setPosition(pos);
}