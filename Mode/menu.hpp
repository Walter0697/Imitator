#pragma once

#include "../renderable.hpp"

#include "../defs.h"

class Menu : public Renderable
{

public:

	Menu();
	~Menu();

	void renderGameOver(sf::RenderWindow&);
	void render(sf::RenderWindow&);

	void setup();
	void changeSelect(int);
	void changeScore(int);

	void unlock();

	bool newModeUnlock = false;
	std::string selectBar[MENU_OPTION];

	sf::Font font;
	sf::Font font2;
	sf::Text title;

	bool storyClicked = false;

	sf::Text unselectedText[MENU_OPTION];
	sf::Text storyText[3];
	sf::Text selectedText;
	sf::Text gameOverText;
	sf::Text restartText;
	sf::Text scoreText;

	sf::Sprite menuplayer;
};