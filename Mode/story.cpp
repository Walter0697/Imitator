#include "story.hpp"
using namespace std;


Story::Story(EnemySet* enemySet, ToolSet* toolSet)
{
	this->enemySet = enemySet;
	this->toolSet = toolSet;

	//initialization
	background = sf::Color(0, 0, 0, 50);
	textColor = sf::Color(0, 0, 0, 255);

	setup(1);

	for (int i = 0; i < dataCols; i++)
	{
		for (int j = 0; j < dataRows[i]; j++)
		{
			cout << mapData[i][j] << "  ";
		}
		cout << endl;
	} 
}

Story::~Story() {}

void Story::setup()
{
	textName.setFont(fontFriend);
	textName.setString("Nothing yet");
	textName.setCharacterSize(40);
	textName.setPosition(40, 820);
	textName.setColor(sf::Color::White);
	textName.setStyle(sf::Text::Bold);

	textDialog = textName;
	textDialog.setCharacterSize(25);
	textDialog.setPosition(40, 900);
	
	textDialog2 = textDialog;
	textDialog2.setPosition(40, 935);

	textCutScene = textDialog;
	textCutScene.setCharacterSize(40);

	textBox.setPosition(20, 800);
	textBox.setSize(sf::Vector2f(760, 180));
	textBox.setFillColor(sf::Color(255, 255, 255, 50));
	textBox.setOutlineColor(sf::Color(255, 255, 255));
	textBox.setOutlineThickness(5);

	cutBox.setPosition(0, 0);
	cutBox.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	cutBox.setFillColor(sf::Color(255, 255, 255, 255));
}

void Story::readFile(std::string filename)
{
	
	std::ifstream fileHndl;
	fileHndl.open(filename);

	fileHndl >> dataCols;

	this->dataRows = new int[dataCols];
	this->mapData = new std::string*[dataCols];

	for (int i = 0; i < dataCols; i++)
	{
		fileHndl >> dataRows[i];

		mapData[i] = new std::string[dataRows[i]];
		for (int j = 0; j < dataRows[i]; j++)
		{
			fileHndl >> mapData[i][j];
		}
	}

	fileHndl.close();

	processing = 0;
	countdown = 0;
	isStory = false;
}

void Story::init()
{
	enemyInfo = 0;
	canContin = true;
}

void Story::setup(int current)
{
	if (mapData != 0)
		clearFile();

	switch (current)
	{
	case 1:
		readFile("Assets/story/story_01.txt");
		break;
	default:
		cout << "fail to read file" << endl;
		break;
	}
}

void Story::update(sf::Time& delta_time)
{
	//countdown
	if (countdown > 0)
		countdown -= delta_time.asMilliseconds();
	
	//stop target enemy
	if (enemyInfo != 0)
	{
		if (enemyInfo->position.y >= target.y)
			enemyInfo->velocity = sf::Vector2f(0, 0);
	}

	//after data read
	if (isStory)
	{
		if (mapData[processing][0] == "DIALOG")
		{
			while (countdown <= 0 && textNow != textNum+1)
			{
				countdown += 80;
				textNow++;
			}
			if (textNow == textNum+1)
			{
				if (line == 1 && dialog2 != "NULL")
				{
					textNow = 0;
					textNum = dialog2.length();
					line = 2;
				}
				else
					canContin = true;
			}
			if (line == 1)
				textDialog.setString(dialog.substr(0, textNow));
			else
				textDialog2.setString(dialog2.substr(0, textNow));
		}
		else if (mapData[processing][0] == "CUTSCENE")
		{
			while (countdown <= 0 && line == 1)
			{
				countdown += 30;
				background.a += 5;
				textColor.a += 5;
			}
			while (countdown <= 0 && line == 3)
			{
				countdown += 30;
				background.a -= 5;
				textColor.a -= 5;
			}

			if (line == 1 && background.a >= 250)
			{
				line = 2;
				countdown = 800;
			}
			else if (line == 2 && countdown <= 0)
				line = 3;
			else if (line == 3 && background.a <= 50)
			{
				isStory = false;
				processing++;
			}
			cutBox.setFillColor(background);
			textCutScene.setColor(textColor);
		}
	}

	//read the data if haven't
	else if (countdown <= 0 && !isStory && processing < dataCols)
	{
		//loading cutscene
		if (mapData[processing][0] == "CUTSCENE")
		{
			dialog = mapData[processing][1];
			replace(dialog.begin(), dialog.end(), '_', ' ');

			setFont(atoi(mapData[processing][2].c_str()));
			background.r = atoi(mapData[processing][3].c_str());
			background.g = atoi(mapData[processing][4].c_str());
			background.b = atoi(mapData[processing][5].c_str());
			background.a = 0;
			cutBox.setFillColor(background);

			textColor.r = atoi(mapData[processing][6].c_str());
			textColor.g = atoi(mapData[processing][7].c_str());
			textColor.b = atoi(mapData[processing][8].c_str());
			textColor.a = 0;
			textCutScene.setColor(textColor);
			textCutScene.setString(dialog);
			textCutScene.setPosition(SCREEN_WIDTH / 2 - textCutScene.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - textCutScene.getLocalBounds().height / 2);

			countdown = 0;
			line = 1;
			isStory = true;
			canContin = false;
		}
		//loading dialog
		else if (mapData[processing][0] == "DIALOG")
		{
			dialog = mapData[processing][1];
			replace(dialog.begin(), dialog.end(), '_', ' ');

			dialog2 = mapData[processing][2];
			replace(dialog2.begin(), dialog2.end(), '_', ' ');

			name = mapData[processing][3];
			replace(name.begin(), name.end(), '_', ' ');

			setFont(atoi(mapData[processing][4].c_str()));

			background.r = atoi(mapData[processing][5].c_str());
			background.g = atoi(mapData[processing][6].c_str());
			background.b = atoi(mapData[processing][7].c_str());
			background.a = 50;
			textBox.setFillColor(background);
			background.a = 255;
			textBox.setOutlineColor(background);

			textColor.r = atoi(mapData[processing][8].c_str());
			textColor.g = atoi(mapData[processing][9].c_str());
			textColor.b = atoi(mapData[processing][10].c_str());
			textColor.a = 255;
			textName.setColor(textColor);
			textDialog.setColor(textColor);
			textDialog2.setColor(textColor);

			textName.setString(name);
			textDialog.setString(dialog.substr(0, 1));
			textDialog2.setString("");

			isStory = true;
			canContin = false;
			countdown = 80;
			textNum = dialog.length();
			textNow = 0;
			line = 1;
		}
		//spawning a specific enemy with objective
		else if (mapData[processing][0] == "ENEMY")
		{
			target = sf::Vector2f(atoi(mapData[processing][2].c_str()), atoi(mapData[processing][3].c_str()));
			targetEnemy(atoi(mapData[processing][1].c_str()), atoi(mapData[processing][2].c_str()));
			processing++;
		}
		//spawning a group of enemies
		else if (mapData[processing][0] == "SPAWN")
		{
			int num = atoi(mapData[processing][2].c_str());
			for (int i = 0; i < num; i++)
			{
				this->enemySet->spawn(atoi(mapData[processing][1].c_str()), (i+1.f)/(num+1.f) * SCREEN_WIDTH);
			}
			processing++;
		}
		//setting up countdown time to wait
		else if (mapData[processing][0] == "WAIT")
		{
			countdown = atoi(mapData[processing][1].c_str());
			processing++;
		}
		//rewards after killing target
		else if (mapData[processing][0] == "OBJECTIVE")
		{
			if (enemySet->checkOutOfBound(*enemyInfo))
			{
				enemyInfo = 0;
				if (mapData[processing][1] == "DIALOG")
					processing++;
				else if (mapData[processing][1] == "TOOL")
				{
					dropTool(atoi(mapData[processing][2].c_str()), atoi(mapData[processing][3].c_str()), atoi(mapData[processing][4].c_str()));
					processing++;
				}
			}
		}
		else if (mapData[processing][0] == "PICTURE")
		{
			processing++;
		}
	}
}

void Story::dropTool(int type, int positionx, int positiony)
{
	switch (type)
	{
	case 1:
		toolSet->shieldTool[toolSet->availableTool(1)].velocity.y = toolSet->shieldTool[0].speed;
		toolSet->shieldTool[toolSet->availableTool(1)].position = sf::Vector2f(positionx, positiony);
		break;
	case 2:
		toolSet->bshieldTool[toolSet->availableTool(2)].velocity.y = toolSet->bshieldTool[0].speed;
		toolSet->bshieldTool[toolSet->availableTool(2)].position = sf::Vector2f(positionx, positiony);
		break;
	case 3:
		toolSet->yshieldTool[toolSet->availableTool(3)].velocity.y = toolSet->yshieldTool[0].speed;
		toolSet->yshieldTool[toolSet->availableTool(3)].position = sf::Vector2f(positionx, positiony);
		break;
	case 4:
		toolSet->healthpack[toolSet->availableTool(4)].velocity.y = toolSet->healthpack[0].speed;
		toolSet->healthpack[toolSet->availableTool(4)].position = sf::Vector2f(positionx, positiony);
		break;
	}
}

void Story::render(sf::RenderWindow& window)
{
	if (processing < dataCols)
	{
		if (mapData[processing][0] == "CUTSCENE" && isStory)
		{
			window.draw(cutBox);
			window.draw(textCutScene);
		}
		else if (mapData[processing][0] == "DIALOG" && isStory)
		{
			window.draw(textBox);

			window.draw(textName);
			window.draw(textDialog);
			window.draw(textDialog2);
		}
	}
}

void Story::setFont(int num)
{
	switch (num)
	{
	case 1:
		textDialog.setFont(fontFriend);
		textDialog2.setFont(fontFriend);
		textName.setFont(fontFriend);
		textCutScene.setFont(fontFriend);
		break;
	case 2:
		textDialog.setFont(fontEnemy);
		textDialog2.setFont(fontEnemy);
		textName.setFont(fontEnemy);
		textCutScene.setFont(fontEnemy);
		break;
	}
}

void Story::targetEnemy(int type, int x_position)
{
	switch (type)
	{
	case 1:
		enemyInfo = &enemySet->denemies[enemySet->avaliableEnemy(1)];
		break;
	case 2:
		enemyInfo = &enemySet->douenemies[enemySet->avaliableEnemy(2)];
		break;
	case 3:
		enemyInfo = &enemySet->lonenemies[enemySet->avaliableEnemy(3)];
		break;
	case 4:
		enemyInfo = &enemySet->shotenemies[enemySet->avaliableEnemy(4)];
		break;
	case 5:
		enemyInfo = &enemySet->gangenemies[enemySet->avaliableEnemy(5)];
		break;
	case 6:
		enemyInfo = &enemySet->thugenemies[enemySet->avaliableEnemy(6)];
		break;
	case 7:
		enemyInfo = &enemySet->unknownenemies[enemySet->avaliableEnemy(7)];
		break;
	case 8:
		enemyInfo = &enemySet->glitchyenemies[enemySet->avaliableEnemy(8)];
		break;
	case 9:
		enemyInfo = &enemySet->advancedenemies[enemySet->avaliableEnemy(9)];
		break;
	case 10:
		enemyInfo = &enemySet->lazzyenemies[enemySet->avaliableEnemy(10)];
		break;
	}
	enemyInfo->position = sf::Vector2f(x_position, -80);
	enemyInfo->velocity.y = enemyInfo->speed;
	enemyInfo->shoot_count = 0;
}

void Story::clearFile()
{
	for (int i = 0; i < dataCols; i++)
	{
		delete[] mapData[i];
	}
	delete[] mapData;
	mapData = 0;
}
