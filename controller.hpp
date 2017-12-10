#pragma once

#include "model.hpp"
#include "view.hpp"

class Controller
{

public:
	Model* model;										//MVC architecture
	View* view;

	Controller(Model* model, View* view);				//constructor
	~Controller();										//destructor

	sf::Event event;									//storing the event

	bool isClick = false;								//check if the user clicking 
	bool keyboardClick = false;							//check if the keyboard clicking button

	bool lastUnlock = false;							//check if the player unlock the last menu options

	int selecting;										//see which options user selecting

	void storyinput(sf::Time);							//input for the story
	void menuinput(sf::Time, sf::RenderWindow&);		//input for the menu
	void scoreinput();									//input inside the scoreboard
	void rewardinput();									//input for the reward screen
	void testerinputs(sf::Time);						//input only avaliable when we are testing
	void inputs(sf::Time);								//general input

	void enter();										//check which option user is in when mouse clicked/enter pressed
	int inOption(float, float);							//check which option is user hovering
};