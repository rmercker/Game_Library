#pragma once
#include "stdafx.h"

class Rock {
private:
	float size;
	float speed;
	bool hit;
	bool drop;
	bool endImage;
	float horizPosition;
	sf::Sprite destroy[4];
	sf::Texture destroy_text[4];
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Rock();

	float getSize() { return size; };			//return scale value
	float getSpeed() { return speed; };		//return speed
	float getPosition() { return horizPosition; };	//return the position where it starts on screen
	sf::Sprite &getSprite() { return sprite; };		//return the sprite for print to screen
	sf::Sprite &getDestroy(int k) { return destroy[k]; }
	bool getHit();
	bool getDrop();
	bool getEndImage() { return endImage; }

	void setSpeed(float speed);			//setters incase we need them
	void setSize(float size);
	void setPosition(float time);
	void setHit(bool val);
	void setDrop(bool val);
	void setEndImage(bool val);

};

