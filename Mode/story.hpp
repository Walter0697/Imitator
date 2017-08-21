#pragma once

#include "../renderable.hpp"

#include "../enemyset.hpp"
#include "../Enemy/enemy.hpp"
#include "../toolSet.hpp"
#include "../Tools/tool.hpp"
#include "../player.hpp"
#include "dropRate.hpp"

#include "../defs.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

class Story : public Renderable
{

public:

	EnemySet* enemySet;
	ToolSet* toolSet;
	DropRate* droprate;
	Player* player;
	Story(EnemySet* enemySet, ToolSet* toolSet, DropRate* droprate, Player* player);
	~Story();

	//mode related
	int currentStory = 1;
	int toolUnlock = 0;

	int processing = 0;
	bool isStory = false;
	bool canContin = false;

	void init();
	void setup();
	void setup(int);
	void update(sf::Time&);
	void render(sf::RenderWindow&);

	//file related
	void clearFile();
	void readFile(std::string);
	
	//action related
	void dropTool(int, int, int);
	void targetEnemy(int, int);
	void setFont(int);
	void spriteAppear(int, int, int);

	//countdown related
	float countdown;

	//map information
	int dataCols;
	int* dataRows;
	std::string** mapData;

	//Variable to render
	//color to render
	sf::Color background;
	sf::Color textColor;

	//text to render
	std::string dialog;
	std::string dialog2;
	std::string name;

	//Enemy information
	Enemy* enemyInfo;
	sf::Vector2f target;

	//Sprite information
	sf::Sprite sprite[5];

	//font related
	sf::Font fontVictory;
	sf::Font fontFriend;
	sf::Font fontEnemy;

	//text related
	sf::Text textName;
	sf::Text textDialog;
	sf::Text textDialog2;
	sf::Text textCutScene;

	sf::Text textMission;
	sf::Text textComplete;
	sf::Text textScore;

	//text box related
	sf::RectangleShape textBox;
	sf::RectangleShape cutBox;

	//text number related
	int textNum;
	int textNow;
	int line;

	//sprite related
	sf::Sprite arrow;
};