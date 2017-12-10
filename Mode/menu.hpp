#pragma once

#include "../renderable.hpp"

#include "../defs.h"

class Menu : public Renderable
{

public:

	Menu();									//constructor
	~Menu();								//destructor

	void renderGameOver(sf::RenderWindow&); //when game is over
	void render(sf::RenderWindow&);			//render

	void setup();							//setup
	void changeSelect(int);					//change the selection in the menu
	void changeScore(int);

	void unlock();							//unlock the selection when player finished the boss fight

	bool newModeUnlock = false;				//if the new selection is unlocked
	std::string selectBar[MENU_OPTION];		//string of the select bar
		
	sf::Font font;							//font and text
	sf::Font font2;
	sf::Text title;

	bool storyClicked = false;				//if story mode clicked

	sf::Text unselectedText[MENU_OPTION];	//text related for the main menu
	sf::Text storyText[3];
	sf::Text selectedText;
	sf::Text gameOverText;
	sf::Text restartText;
	sf::Text scoreText;

	sf::Sprite menuplayer;
};