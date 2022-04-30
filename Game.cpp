#include <SFML/Graphics.hpp>
#include "Road.h"
#include "const.h"
#include "Game.h"
#include "barrier.h"
#include "Splash.h"

Game::Game() : window(sf::VideoMode(N* ts, M* ts), "Xonix Game!"),
player(500.f, 500.f), window_borders(sf::Vector2f(WINDOW_WIDTH - 35, WINDOW_HEIGHT - 35)),
splash_screen(SPLASH_FILE_NAME, 1.2f, 1.43f),


game_over_screen(FILE_OVER, 2.f, 3.f),//500 200
laser(500.f,600.f)
{
	
	window.setFramerateLimit(60);
	meteor_sprites.reserve(METEORS_QTY);	
	for (size_t i = 0; i < METEORS_QTY; i++) {
		meteor_sprites.push_back(new Meteor());
	}
	window_borders.setPosition(17,13);
	window_borders.setOutlineColor(sf::Color::Yellow);
	window_borders.setFillColor(sf::Color::Transparent);
	window_borders.setOutlineThickness(35);
}

void Game::play(){
	while (window.isOpen()) {
		check_event();
		update();
		check_collisions();
		draw();
		
	}
}

void Game::check_event() {

	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space && game_state == SPLASH) {
				game_state = PLAY;
			}

		}
		else
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Time elapsed = clock.getElapsedTime();
				if (elapsed.asMilliseconds() > 250) {
					laser_sprites.push_back(new Laser(player.getPosition().x +
						player.getWidth() / 10, player.getPosition().y));
					clock.restart();
				}
			}
	}
}
void Game::update() {
		switch (game_state) {
		case SPLASH:

			break;
		case PLAY:
			player.update();
			for (size_t i = 0; i < METEORS_QTY; i++) {
				meteor_sprites[i]->update();
			}
			for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
				(*it)->update();
			}
			for (auto it = exp_sprites.begin(); it != exp_sprites.end(); it++) {
				(*it)->update();
			}

			break;
		case GAME_OVER:
			break;
		}
		
	}
void Game::draw() {
	
	switch (game_state) {
	case SPLASH:

		window.clear(sf::Color::White);
		window.draw(splash_screen.getSprite());
		break;

	case PLAY:
		
		road.draw(window);
		window.draw(window_borders);
		player.draw(window);
		for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
			(*it)->draw(window);
		}
        for (size_t i = 0; i < METEORS_QTY; i++) {
			meteor_sprites[i]->draw(window);
		}
		laser.draw(window);
		for (auto it = exp_sprites.begin(); it != exp_sprites.end(); it++) {
			(*it)->draw(window);
		}

		break;
	case GAME_OVER:
		window.clear(sf::Color::Black);
		window.draw(game_over_screen.getSprite());
		break;

	}


	window.display();
}
void Game::check_collisions() {
	
	for (size_t i = 0; i < METEORS_QTY; i++) {
		if (player.getHitBox().intersects(
			meteor_sprites[i]->getHitBox()))
		{
			player.reduceHp(meteor_sprites[i]->getWidth() / 3);
			meteor_sprites[i]->spawn();
				
		}
	}
	if (player.isDead()) game_state = GAME_OVER;
	for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
		for (size_t i = 0; i < METEORS_QTY; i++) {
			if ((*it)->getHitBox().intersects(meteor_sprites[i]->getHitBox()))
			
			{
				Explosion* new_explosion =
					new Explosion(meteor_sprites[i]->getCenter());
				exp_sprites.push_back(new_explosion);
				meteor_sprites[i]->spawn();

			}
		}





	}
	
}

