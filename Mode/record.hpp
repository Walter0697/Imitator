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
	Record(Player* player, Story* story);							//constructor
	~Record();														//destructor

	void init();													//initialization
	void setup();													//setup
	void readFile();												//read the record if any
	void writeFile();												//write the record to a txt file

	void addRecord(int, std::string);								//add the record after a round
	void render(int, sf::RenderWindow&);							//render
	void render(std::string, int, std::string**, sf::RenderWindow&);//render

	//different information for the record
	int menuUnlock = 0;
	int freezeUnlock = 0;

	int bossDefeated;
	int toolsPicked[6];
	int startPosition = 0;

	int currentx, currenty;
	int shouldRender = 10;

	//store the current and previous record
	int currentRank = -1;
	int currentType = 0;
	int previousStory = -1;
	int previousChaos = -1;

	//array of record
	int numStory;
	std::string** storyRecord;
	int numChaos;
	std::string** chaosRecord;
	std::string** temp;

	//font and text
	sf::Font font;
	sf::Text titleText;
	sf::Text recordText;

	//sprite for the record
	sf::Sprite scoreBoard;
	sf::Sprite bullet_sprite[NUM_OF_BULLET];

	//to show the current record
	sf::RectangleShape recBox;

private:
	void renderString(int, int, std::string, sf::RenderWindow&);
};