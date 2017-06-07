#include "stdafx.h"
#include "Ping.h"

Ping::Ping(sf::RenderWindow *game_window) {
	srand((unsigned int)time(NULL));//Needed to make the seed of rand() different.
	window = game_window;
	//This is to make sure that when you press P for pausing,
	//that it only registers 1 press instead of like a hundred
	window->setKeyRepeatEnabled(false);

	//Load the fontface for the game.
	font.loadFromFile("Fonts/mini-wakuwaku.otf");

	//Load all the sounds.
	sound_buffer[0].loadFromFile("Ping_Sounds/ping.wav");//Left paddle hit
	sound_buffer[1].loadFromFile("Ping_Sounds/pong.wav");//Right paddle hit
	sound_buffer[2].loadFromFile("Ping_Sounds/rip.wav");//Point scored
	sound_buffer[3].loadFromFile("Ping_Sounds/good job.wav"); //Game end
	sound_effect.setBuffer(sound_buffer[0]);

	//Initializing the text that displays the player scores
	player1_text.setFont(font);
	player1_text.setCharacterSize(32);
	player1_text.setColor(sf::Color(255, 204, 102));
	player1_text.setStyle(sf::Text::Bold);
	player1_text.setString("0");
	//Calculating the positions of the score text
	float player1_text_width = player1_text.getLocalBounds().width;
	float player1_text_height = player1_text.getLocalBounds().height;
	float player1_text_xpos = (window->getSize().x - player1_text_width) / 2 - 3 * player1_text_width;
	player1_text.setPosition(sf::Vector2f(player1_text_xpos, 0));

	float player2_text_xpos = (window->getSize().x - player1_text_width) / 2 + 3 * player1_text_width;
	player2_text = player1_text; //Copy all the formatting of player1_text
	player2_text.setPosition(sf::Vector2f(player2_text_xpos, 0));

	//Initializing the win text
	win_text.setFont(font);
	win_text.setCharacterSize(64);
	win_text.setColor(sf::Color(255, 204, 102));
	win_text.setStyle(sf::Text::Bold);

	//Creating the left and right paddle
	player_startposition = sf::Vector2f(0, -40 + (float)window->getSize().y / 2);
	player = new Paddle(player_startposition, "Ping_Images/left ping paddle.png");

	opponent_startposition = sf::Vector2f((float)window->getSize().x -
		(float)player->getSize().x, -40 + (float)window->getSize().y / 2);
	opponent = new Paddle(opponent_startposition, "Ping_Images/right ping paddle.png");

	//Creating the ball
	{
		//The ternary operator (condition) ? iftrue : iffalse
		//is being used to make the ball's x direction and y direction
		//negative based on a 50 / 50 chance.
		//Note that this is necessary because I'm using discrete values 
		//instead of a continous range, solely for balancing reasons.
		random_negative = rand() % 10 + 1;

		ball_xdirection = (random_negative > 5) ?
			((rand() % 4 + 3) / 1000.0f) : ((rand() % 4 + 3)*-1 / 1000.0f);

		random_negative = rand() % 10 + 1;

		ball_ydirection = (random_negative > 5) ?
			((rand() % 3 + 3) / 1000.0f) : ((rand() % 3 + 3)*-1 / 1000.0f);

		ball_startposition = sf::Vector2f((float)window->getSize().x / 2, (float)window->getSize().y / 2);
		ball_startdirection = sf::Vector2f(ball_xdirection, ball_ydirection);
		ball_speed = 60;

		ball = new Ball(ball_startposition, ball_startdirection, ball_speed);
	}

	//Line for top of screen
	line = sf::RectangleShape(sf::Vector2f((float)window->getSize().x, 2));
	line.move(sf::Vector2f(0, 38));
	line.setFillColor(sf::Color(255, 204, 102));

	//Line to divide the scores
	line_divider = sf::RectangleShape(sf::Vector2f(1, 28));
	line_divider.move(sf::Vector2f((float)window->getSize().x / 2, 6));
	line_divider.setFillColor(sf::Color(255, 204, 102));
	//Keeps track of when a point is scored
	reset = false;

	//Keeps track of player scores
	player1_score = 0;
	player2_score = 0;

	//Maintains the game logic
	paused = false;
	game_wait = true;
	player1_has_scored = false;
	player1_win = false;
}

//This updates the game each frame.
void Ping::updateGame() {

	//Reset the positions of everything after a point gets scored
	if (reset == true) {
		//Reset the paddle positions
		player->setPosition(player_startposition);
		opponent->setPosition(opponent_startposition);

		//Increase the ball speed for the new level
		ball_speed = 60 + 2 * ((float)player1_score + (float)player2_score);

		//Recalculate a new direction for the ball
		if (player1_has_scored == true) {
			ball_xdirection = ((rand() % 3 + 3)*-1 / 1000.0f);
		}
		else {
			ball_xdirection = ((rand() % 3 + 3) / 1000.0f);
		}
		random_negative = rand() % 10 + 1;
		ball_ydirection = (random_negative > 5) ?
			((rand() % 3 + 3) / 1000.0f) : ((rand() % 3 + 3)*-1 / 1000.0f);
		ball_startdirection = sf::Vector2f(ball_xdirection, ball_ydirection);

		//Create a new ball based on the above. Start position remains
		//at the center of the screen.
		delete ball;
		ball = new Ball(ball_startposition, ball_startdirection, ball_speed);

		reset = false;
		game_wait = true; //This is to freeze the game. See startGame()
	}


	//Only update the game if it isn't paused.
	if (paused == false) {
		//Read player inputs.
		{
			//Read in keyboard input to move the first player's paddle.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
				player->getPosition().y >= 40)
				player->move('u');
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
				player->getPosition().y + player->getSize().y <= window->getSize().y)
				player->move('d');

			//Read in keyboard input to move the second player's paddle.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				opponent->getPosition().y >= 40)
				opponent->move('u');
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				opponent->getPosition().y + opponent->getSize().y <= window->getSize().y)
				opponent->move('d');
		}

		//Collision detection + boundary detection
		{
			//Ball Collision with the right paddle
			if (ball->getPosition().x + ball->getSize().x >= opponent->getPosition().x &&
				ball->getPosition().y + ball->getSize().y >= opponent->getPosition().y &&
				ball->getPosition().y <= opponent->getPosition().y + opponent->getSize().y)
			{
				sound_effect.setBuffer(sound_buffer[0]);
				sound_effect.play();
				ball_speed += 2 + (player1_score + player2_score) / 2;
				ball->reflectX();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ball->getDirection().y > 0)
					ball->reflectY();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ball->getDirection().y < 0)
					ball->reflectY();
			}
			//Ball goes past the right paddle
			else if (ball->getPosition().x + ball->getSize().x >= opponent->getPosition().x &&
				(ball->getPosition().y > opponent->getPosition().y + opponent->getSize().y ||
					ball->getPosition().y < opponent->getPosition().y))
			{
				sound_effect.setBuffer(sound_buffer[2]);
				sound_effect.play();
				player1_score++;
				if (player1_score == 5)
					player1_win = true;
				player1_has_scored = true;
				reset = true;
				sf::sleep(sf::seconds(3));
			}
			//Ball collision with the left paddle
			if (ball->getPosition().x <= player->getPosition().x + player->getSize().x &&
				ball->getPosition().y + ball->getSize().y >= player->getPosition().y &&
				ball->getPosition().y <= player->getPosition().y + player->getSize().y)
			{
				sound_effect.setBuffer(sound_buffer[1]);
				sound_effect.play();
				ball_speed += 2 + (player1_score + player2_score) / 2;
				ball->reflectX();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && ball->getDirection().y > 0)
					ball->reflectY();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ball->getDirection().y < 0)
					ball->reflectY();
			}
			//Ball goes past the left paddle
			else if (ball->getPosition().x <= player->getPosition().x + player->getSize().x &&
				(ball->getPosition().y > player->getPosition().y + player->getSize().y ||
					ball->getPosition().y < player->getPosition().y))
			{
				sound_effect.setBuffer(sound_buffer[2]);
				sound_effect.play();
				player2_score++;
				if (player2_score == 5)
					player1_win = false;
				player1_has_scored = false;
				reset = true;
				sf::sleep(sf::seconds(3));
			}

			//Ball collision with the top or bottom of the screen
			if (ball->getPosition().y <= 40 ||
				ball->getPosition().y + ball->getSize().y >= window->getSize().y)
				ball->reflectY();
		}

		//Update the ball's position
		{
			ball->setSpeed(ball_speed);
			ball->update();
		}

		//Update the text to display the current score
		{
			player1_text.setString(std::to_string(player1_score));
			player2_text.setString(std::to_string(player2_score));
		}
	}

}

//This draws each object in the game.
void Ping::drawGame() {
	window->clear(sf::Color(255, 242, 235, 0));
	window->draw(line);
	window->draw(line_divider);
	window->draw(player1_text);
	window->draw(player2_text);
	window->draw(player->sprite());
	window->draw(opponent->sprite());
	window->draw(ball->sprite());
	window->draw(win_text);
	window->display();
}

//This is where the main loop of the program is located. This
//is the only thing meant to be called outside of the class.
void Ping::startGame() {

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
				//Pauses the game.
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::P)
					paused = !paused;
				break;
			default:
				break;
			}
		}


		if (player1_score < 5 && player2_score < 5) {
			//Update the game each frame
			updateGame();
			//Draw the game each frame
			drawGame();
		}
		else {
			if (player1_win == true)
				win_text.setString("Player 1 Wins");
			else
				win_text.setString("Player 2 Wins");

			//Calculating the position of win text
			float win_text_width = win_text.getLocalBounds().width;
			float win_text_height = win_text.getLocalBounds().height;
			float win_text_xpos = (window->getSize().x - win_text_width) / 2;
			float win_text_ypos = (window->getSize().y - win_text_height) / 4;
			win_text.setPosition(win_text_xpos, win_text_ypos);

			drawGame(); // Update the game end text
			sound_effect.setBuffer(sound_buffer[3]);
			sound_effect.play();//Play the game end noise
			sf::sleep(sf::seconds(5)); //Wait 4 seconds
			return; // Exit the game
		}
		//This freezes the game at the start of a round for 1 second.
		if (game_wait) {
			sf::sleep(sf::seconds(1));
			game_wait = false;
		}

	}
}