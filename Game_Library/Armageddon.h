#pragma once
#include "stdafx.h"
#include "Gun.h"

class Armageddon {
private:
	sf::Sprite background;
	sf::Sprite life;
	sf::RenderWindow *window;
	sf::Event event;
	sf::Font font;
	sf::Text madeHighScore;
	sf::Text leaderBoard;
	sf::Text score;
	sf::Text roundPause;
public:
	sf::Clock clock;
	float time;
	Armageddon(sf::RenderWindow *window);
	sf::Sprite getBackground();

	void GAME_LOOP();
};