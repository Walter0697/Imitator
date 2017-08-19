#pragma once

#include "../player.hpp"

#include "../defs.h"
#include <fstream>
#include <iostream>

class Record
{

public:

	Player* player;
	Record(Player* player);
	~Record();

	void init();
	void readFile();

	void addRecord(int, std::string);
	void render(int, sf::RenderWindow&);
	void render(std::string, std::string**, sf::RenderWindow&);

	int currentStory;
	int toolsPicked[6];

	int numStory;
	std::string** storyRecord;
	int numChaos;
	std::string** chaosRecord;
	std::string** temp;

	sf::Font font;
	sf::Text storyText;
	sf::Text chaosText;
	sf::Text recordText;

	sf::Sprite scoreBoard;
};