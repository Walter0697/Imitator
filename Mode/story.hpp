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

	//mode related
	int currentStory = 1;
	int processing = 0;
	bool isStory = false;

	void setup(int);
	void update(sf::Time&);
	void render(sf::RenderWindow&);

	//file related
	void clearFile();
	void readFile(std::string);
	
	//action related
	void targetEnemy(int, int);
	void setFont(int);

	//countdown related
	float countdown;

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

	//font related
	sf::Font fontFriend;
	sf::Font fontEnemy;

	//text related
	sf::Text textDialog;
	sf::Text textName;

	//text number related
	int textNum;
	int textNow;

	//objective related
	int objective;
};