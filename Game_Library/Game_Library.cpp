// Game_Library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bullets.h"
#include "Gun.h"
#include "Armageddon.h"
#include "Rock.h"
#include "Ping.h"

int main()
{
	sf::Clock clock;
	enum menu_options {Title, Menu, Armageddon_Game, Ping_Game}; // allows game to keep track of where it is
	menu_options option = Title;
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1080, 760, 32), "Game Library", sf::Style::Default); // window used by whole program
	sf::Event event;
	while (window->isOpen()) {
		if (option == Title) {
			sf::Font font;
			if (!font.loadFromFile("Fonts/comicz.ttf")) {
				abort();
			}
			sf::Text welcome;
			sf::Text info;
			float scale = 1;
			float time = clock.getElapsedTime().asSeconds();
			bool increase = true;

			welcome.setFont(font); // setting up game window for the whole program
			welcome.setOrigin(400, 30);
			welcome.setPosition(585, 380);
			welcome.setCharacterSize(48);
			welcome.setColor(sf::Color::Green);
			welcome.setString("Welcome to the game Library!");
			
			info.setFont(font); // tells user what key to press to move on
			info.setString("Press any key to continue");
			info.setCharacterSize(22);
			info.setColor(sf::Color::Magenta);
			info.setPosition(420, 420);

			while (window->isOpen() && option == Title){ // title screen
			window->clear();
			if (welcome.getScale().x < 1.5 && increase) { // used to make welcome text grow to certain size and then shrink (repeats process)
				scale += (float) pow(time, 5);
				welcome.setScale((float) scale, (float) scale);
			}
			else increase = false;
			if (welcome.getScale().x > 0 && !increase) {
				scale -= (float) pow(time, 5);
				welcome.setScale((float) scale, (float) scale);
			}
			else increase = true;

			window->draw(info);
			window->draw(welcome);
			window->display();
			while (window->pollEvent(event) && option == Title) { //allows user to go from title to main menu or to exit
				if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
					option = Menu;
				}
				if (event.type == sf::Event::Closed) {
					window->close();
				}
			}
		}
		}

		else if (option == Menu) { // main menu where player decides what game to play
				sf::Texture texture;
				if (!texture.loadFromFile("Menu_Images/Menu.Png")) {
					abort();
				}
			sf::Sprite menu;
			menu.setTexture(texture);
			sf::FloatRect armageddon(10,160,1060,260); //used to determine if armageddon is picked
			sf::FloatRect ping(10,380,1060,210); //is ping picked
			sf::FloatRect exit(10,605,1060,145); // does the user wish to exit
			float time = clock.restart().asSeconds();

			while(window->isOpen() && option == Menu) { // used to determine where user clicks on screen
				window->clear();
				window->draw(menu);
				window->display();
				while (window->pollEvent(event)) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (armageddon.contains((float) sf::Mouse::getPosition().x, (float) sf::Mouse::getPosition().y)) { //did user pick armageddon
							option = Armageddon_Game;
						}
						if (ping.contains((float) sf::Mouse::getPosition().x, (float) sf::Mouse::getPosition().y)) { // did user pick ping
							option = Ping_Game;
						}
						if (exit.contains((float) sf::Mouse::getPosition().x, (float) sf::Mouse::getPosition().y)) { // does the user wish to exit
							window->close();
						}
					}
					if (event.type == sf::Event::Closed) {
						window->close();
					}
				}
				
			}
		}

		else if (option == Armageddon_Game) { // armageddon game, runs when user selects armageddon on main menu
			window->clear();
			sf::Sprite tutorial;
			sf::Texture guide;
			if (!guide.loadFromFile("Menu_Images/Armageddon_Tutorial.Png")) {
				abort();
			}
			tutorial.setTexture(guide);
			window->draw(tutorial);
			window->display();
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
					//play game
					Armageddon game(window);
					game.GAME_LOOP();
					option = Menu; // returns to menu after game ends
				}
			}
		}

		else if (option == Ping_Game) { // plays the Ping game if user selects it from main menu
			window->clear();
			sf::Sprite tutorial;
			sf::Texture guide;
			if (!guide.loadFromFile("Menu_Images/Ping_Tutorial.Png")) {
				abort();
			}
			tutorial.setTexture(guide);
			window->draw(tutorial);
			window->display();
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
					//play game
					Ping ping(window);
					ping.startGame();
					option = Menu; // returns to menu after game ends
				}
			}
		}
	}
    return 0;
}

