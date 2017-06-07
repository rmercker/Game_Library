#pragma once
#include "stdafx.h"
#include "Paddle.h"
#include "Ball.h"

class Ping {
	sf::RenderWindow *window;
	sf::Font font;
	sf::Text player1_text, player2_text, win_text;
	sf::SoundBuffer sound_buffer[4];
	sf::Sound sound_effect;
	sf::RectangleShape line, line_divider;
	Ball *ball;
	Paddle *player, *opponent;
	sf::Vector2f player_startposition, opponent_startposition,
		ball_startdirection, ball_startposition;
	bool paused, reset, game_wait, player1_has_scored, player1_win;
	int player1_score, player2_score, random_negative;
	float ball_speed, ball_xdirection, ball_ydirection;

	void updateGame();
	void drawGame();
public:
	Ping(sf::RenderWindow*);
	void startGame();
};