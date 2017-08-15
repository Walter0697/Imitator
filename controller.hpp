#pragma once

#include "model.hpp"
#include "view.hpp"

class Controller
{

public:
	Model* model;
	View* view;

	sf::Event event;

	int selecting;
	Controller(Model* model, View* view);
	~Controller();

	void menuinput(sf::Time, sf::RenderWindow&);
	void testerinputs(sf::Time);
	void inputs(sf::Time);
};