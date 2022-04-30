#pragma once
#include "player.h"
#include "Road.h"
#include "barrier.h"
#include "Splash.h"
#include <list>
#include "laser.h"
#include "explosion.h"

class Game {
public:
	enum GameState { SPLASH, PLAY, GAME_OVER };
	Game();
	void play();
	void check_event();
	void update();
	void draw();
	void check_collisions();
	
private:

	sf::RenderWindow window;
    GameState game_state{ SPLASH};
	Player player;
	sf::RectangleShape window_borders;
	Road road;
	std::vector<Meteor*> meteor_sprites;
	SplashScreen splash_screen, game_over_screen;
	sf::Clock clock;
	std::list<Laser*> laser_sprites;
	Laser laser;
	std::list<Explosion*> exp_sprites;
	


	
};