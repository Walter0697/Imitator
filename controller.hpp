#pragma once

#include "model.hpp"
#include "view.hpp"

class Controller
{

public:
	Model* model;
	View* view;

	sf::Event event;

	bool isClick = false;
	bool keyboardClick = false;

	bool lastUnlock = false;

	int selecting;
	Controller(Model* model, View* view);
	~Controller();

	void storyinput(sf::Time);
	void menuinput(sf::Time, sf::RenderWindow&);
	void scoreinput();
	void rewardinput();
	void testerinputs(sf::Time);
	void inputs(sf::Time);

	void enter();
	int inOption(float, float);
};