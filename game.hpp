#pragma once

#include <SFML/Graphics.hpp>

#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"

class Game
{

public:

	Model* model;
	View* view;
	Controller* controller;					//fit in the MVC architecture

	Game();
	~Game();

	//nesscary variable for the game
	sf::Clock clock;

	void loop();

};