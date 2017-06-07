#include "stdafx.h"
#include "Armageddon.h"
#include "Rock.h"
#include "Bullets.h"
#include "Rounds.h"
#include "HighScore.h"

Armageddon::Armageddon(sf::RenderWindow *window) { // constructing default values used in the game
	this->window = window;						   // setting text strings to be displayed in game
	time = clock.restart().asSeconds();
	if (!font.loadFromFile("Fonts/comicz.ttf")) {
		abort();
	}
	score.setFont(font);
	score.setCharacterSize(48);
	score.setColor(sf::Color::Red);
	score.setString("Round 1: Score = 0 live(s) = 3");

	roundPause.setFont(font);
	roundPause.setCharacterSize(30);
	roundPause.setPosition(500, 330);
	roundPause.setColor(sf::Color::Red);

	madeHighScore.setFont(font);
	madeHighScore.setCharacterSize(30);
	madeHighScore.setPosition(150, 40);
	madeHighScore.setString("You have just entered the High Score Hall of Fame!!!\n    Please enter your initials and then press enter");

	leaderBoard.setFont(font);
	leaderBoard.setCharacterSize(48);
}

sf::Sprite Armageddon::getBackground() { // background image
	return background;
}

void Armageddon::GAME_LOOP() { // The game itself
	//Where the magic happens
	window->clear();

	HighScore scoretext;


	sf::Texture backdrop; // back ground
	if (!backdrop.loadFromFile("Armageddon_Images/Background.png")) {
		abort();
	}
	background.setTexture(backdrop);

	sf::Texture life_image; // image of tank to represent life count
	if (!life_image.loadFromFile("Armageddon_Images/Turret.png")) {
		abort();
	}
	life.setTexture(life_image);
	life.setScale(.1f, .1f);

	sf::Music music_Tank; //tank firing
	sf::Music music_Rock; //rock exploding

	if (!music_Tank.openFromFile("Armageddon_Sounds/Tank_Fire.ogg")) {
		abort();
	}

	if (!music_Rock.openFromFile("Armageddon_Sounds/Rock_Explosion.ogg")) {
		abort();
	}

	music_Tank.setVolume(50);

	Rounds round; // setting up round
	round.setRock();
	round.setOver(false);

	int numround = round.getRound();
	int numrock = round.getRock();
	
	Gun gun; // setting up the rocks and bullets for game
	Rock *rock = new Rock[round.getRock()];
	rock[0].setDrop(true);
	Bullets *bill = new Bullets[10];

	bool exit_score = false; //used for high score menu

	while (window->isOpen()) {
		while (gun.getHealth(0)) { //round brackets to help control where the game is if health = 0 game over
			
			if (numround < round.getRound()) { // determines if new round has started
				roundPause.setString("Round: " + std::to_string(round.getRound()));
				while (clock.getElapsedTime().asSeconds() < 3) {
					window->clear();
					window->draw(roundPause);
					window->display();
				}
				clock.restart();
				numround = round.getRound();
				if (numround % 3 == 0) {
					int k = 0;
					while (k != 10 && gun.getHealth(k)) {
							k++;
					}
					if (k < 10) {
						gun.setHealth(k, true);
					}
				}
				round.setRock();
				numrock = round.getRock();
				round.setOver(false);
				rock = new Rock[round.getRock()];
				rock[0].setDrop(true);
			}

			time = clock.restart().asSeconds();
		
			window->clear();
			window->draw(background);

			 // Movement block for bullets and tank
				for (int i = 0; i < 10; i++) { // draw each bullet that is fired
					if (bill[i].getFired()) {
						bill[i].movementCalc(time);
						window->draw(bill[i].getSprite());
					}
					if (bill[i].getSprite().getPosition().y < 0) {
						bill[i].setFired(false);
						bill[i].getSprite().setPosition(-100, 1);
					}
				}

				window->draw(gun.getSprite());

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { //tank left
					if (gun.getSprite().getPosition().x < 0) {

					}
					else
						gun.movementCalc(-1, time);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { //tank right
					if (gun.getSprite().getPosition().x > 1030) {

					}
					else
						gun.movementCalc(1, time);
				}

				while (window->pollEvent(event)) { // did player fire or close window
					if (event.type == sf::Event::Closed) {
						window->close();
					}
					if (event.key.code == sf::Keyboard::Up) {
						for (int i = 0; i < 10; i++) {
							if (!bill[i].getFired()) {
								bill[i].setFired(true);
								music_Tank.play();
								bill[i].getSprite().setPosition(gun.getSprite().getPosition().x + 25, gun.getSprite().getPosition().y);

								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { // is tank moving left
									bill[i].setDirection(-1);
									gun.movementCalc(-1, time);
								}
								else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { // is tank moving right
									bill[i].setDirection(1);
									gun.movementCalc(1, time);
								}
								else { // tank is not moving
									bill[i].setDirection(0);
								}
								break;
							}
						}
					}
				}
			 // end tank/bullet movement block

				 // rock movement block

					for (int i = 0; i < round.getRock(); i++) { // should next rock drop yet
						if (i > 0 && rock[i-1].getSprite().getPosition().y - rock[i].getSprite().getPosition().y > 200) {
							if (!rock[i].getDrop() && !rock[i].getHit()) {
								rock[i].setDrop(true);
							}
						}
						if (rock[i].getDrop()) { // drawing all rocks
							rock[i].getSprite().move(0, 300 * time);
							for (int k = 0; k < 4; k++) {
								rock[i].getDestroy(k).move(0, 300 * time);
							}
							window->draw(rock[i].getSprite());
						}
						if (rock[i].getSprite().getPosition().y > 660 && !rock[i].getHit()) { // rock hits ground
							for (int k = 9; k >= 0; k--) {
								if (gun.getHealth(k)) {
									gun.setHealth(k, false);
									break;
								}
							}
							rock[i].setHit(true);
							rock[i].setDrop(false);
							numrock--;
						}
						if (rock[i].getHit() && !rock[i].getEndImage()) { // rock is hit, displays destruction of rock
							for (int k = 0; k < 4; k++) {
								rock[i].getDestroy(k).move((float) (pow(-1, k)) * .15f, 300 * time);
								window->draw(rock[i].getDestroy(k));
							}
						}
					}


			 // end rock movement block

			{ // collision block

				for (int i = 0; i < round.getRock(); i++) { //rock loop, i represents the rock iterator
					if (!rock[i].getDrop() || rock[i].getHit()) continue;
					for (int j = 0; j < 10; j++) { //bullet loop, j represents bullet iterator
						if (!bill[j].getFired()) continue;
						if (bill[j].getSprite().getPosition().x > rock[i].getSprite().getPosition().x + 20
							&& bill[j].getSprite().getPosition().x < rock[i].getSprite().getPosition().x + 90
							&& bill[j].getSprite().getPosition().y > rock[i].getSprite().getPosition().y + 10
							&& bill[j].getSprite().getPosition().y < rock[i].getSprite().getPosition().y + 50) {

							rock[i].setHit(true), rock[i].setDrop(false);
							bill[j].setFired(false);
							music_Rock.play();
							round.setScore();
							numrock--;
						}
					}
				}

			} // end collision block

			{ // round manipulation
				if (gun.getHealth(0) && numrock <= 0) {
					round.setOver(true);
				}
				if (round.getOver()) {
					round.setRound();
				}

			} // end round manipulation

			 //text update based on score/health

				score.setString(std::to_string(round.getScore()));
				for (int i = 0; i < 10; i++) {
					if (gun.getHealth(i)) {
						life.setPosition(0 + 30 * i, 60.0f);
						window->draw(life);
					}
				}
				window->draw(score);

			 // end text update block

				window->display();

		}

		if (scoretext.determineHigh(round.getScore()) && !exit_score) { // if player gets top ten they get into highscore
			std::string name = "";
			while (true) {
				window->clear();
				window->draw(madeHighScore);
				window->display();
				while (window->pollEvent(event)) {
					if (event.type == sf::Event::TextEntered) {
						if (event.text.unicode < 128) {
							name += static_cast<char>(event.text.unicode);
						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					exit_score = true;
					break;
				}
			}
			if (name.length() < 3) { // ensures a length of 3
				while (name.length() < 3) {
					name += " ";
				}
			}
			scoretext.newHigh(name, round.getScore());
			scoretext.highScore();
		}

		window->clear(); // exit message after game ends

		for (int i = 0; i < 10; i++) {
				leaderBoard.setPosition(300, 40 + 60 * i);
				leaderBoard.setString(std::to_string(i + 1) + ") " + scoretext.printHigh(i, 0) + ": " + scoretext.printHigh(i, 1));
				window->draw(leaderBoard);
		}

		// sets up score menu after game, shows round, score, and leaderboard
		score.setString("GAME OVER!\nRound: " + std::to_string(round.getRound()) + "\nScore: " + std::to_string(round.getScore()));
		score.setPosition(0, 0);
		window->draw(score);
		score.setString("Press Any Key To Continue");
		score.setPosition(230, 650);
		window->draw(score);
		window->display();

		while (window->pollEvent(event) && clock.getElapsedTime().asSeconds() > 2) { // close window after game over
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) { // user continues to main menu
				return;
			}
		}
	}
}