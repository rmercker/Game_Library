#pragma once
#include "stdafx.h"

//Paddle class is used for both player 1 and player 2.
class Paddle {
	sf::Texture paddleTexture;
	sf::Sprite paddleSprite;

public:
	Paddle(sf::Vector2f spritePosition, sf::String str);
	void move(char);
	void setPosition(sf::Vector2f&);
	sf::Sprite sprite() { return paddleSprite; };
	sf::Texture texture() { return paddleTexture; };
	sf::Vector2u getSize() { return paddleTexture.getSize(); };
	sf::Vector2f getPosition() { return paddleSprite.getPosition(); };


};