#pragma once

#include "../renderable.hpp"

#include "../enemyset.hpp"
#include "../Enemy/enemy.hpp"

#include "../defs.h"
#include <fstream>
#include <iostream>
#include <string>

class Story : public Renderable
{

public:

	EnemySet* enemySet;
	Story(EnemySet* enemySet);
	~Story();

	void setup();
	void update(sf::Time&);
	void render(sf::RenderWindow&);

	void clearFile();
	void readFile(std::string);
	void action(std::string);
	
	//countdown related
	float countdown;
	bool isStory = false;
	int processing = 0;

	//map information
	int dataCols;
	int* dataRows;
	std::string** mapData;

	//Variable to render
	//color to render
	sf::Color background;
	sf::Color textColorOne;
	sf::Color textColorTwo;

	//text to render
	std::string dialog;
	std::string name;

	//Enemy information
	Enemy* enemyInfo;
	sf::Vector2f target;

	//Sprite information
	sf::Sprite sprite;

	//text related
	sf::Font font;
	sf::Text text;

	//objective related
	int objective;
};