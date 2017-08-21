#pragma once

#include "../player.hpp"
#include "story.hpp"

#include "../defs.h"
#include <fstream>
#include <iostream>

class Record
{

public:

	Player* player;
	Story* story;
	Record(Player* player, Story* story);
	~Record();

	void init();
	void setup();
	void readFile();
	void writeFile();

	void addRecord(int, std::string);
	void render(int, sf::RenderWindow&);
	void render(std::string, int, std::string**, sf::RenderWindow&);

	int toolsPicked[6];
	int startPosition = 0;

	int currentx, currenty;
	int shouldRender = 10;

	int currentRank = -1;
	int currentType = 0;
	int previousStory = -1;
	int previousChaos = -1;

	int numStory;
	std::string** storyRecord;
	int numChaos;
	std::string** chaosRecord;
	std::string** temp;

	sf::Font font;
	sf::Text titleText;
	sf::Text recordText;

	sf::Sprite scoreBoard;
	sf::Sprite bullet_sprite[NUM_OF_BULLET];

	sf::RectangleShape recBox;

private:
	void renderString(int, int, std::string, sf::RenderWindow&);
};