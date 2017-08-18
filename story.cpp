#include "story.hpp"
using namespace std;


Story::Story(EnemySet* enemySet)
{
	this->enemySet = enemySet;

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

	textBox.setPosition(20, 800);
	textBox.setSize(sf::Vector2f(760, 180));
	textBox.setFillColor(sf::Color(255, 255, 255, 50));
	textBox.setOutlineColor(sf::Color(255, 255, 255));
	textBox.setOutlineThickness(5);
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
	if (isStory && mapData[processing][0] == "DIALOG")
	{
		if (mapData[processing][0] == "DIALOG")
		{
			while (countdown <= 100 && textNow != textNum)
			{
				textNow++;
			}
			textDialog.setString(dialog.substr(0, textNow));
		}
	}
	//read the data if haven't
	else if (countdown <= 0 && !isStory)
	{
		if (mapData[processing][0] == "CUTSCENE")
		{
			dialog = mapData[processing][1];
			setFont(atoi(mapData[processing][2].c_str()));
			background.r = atoi(mapData[processing][3].c_str());
			background.g = atoi(mapData[processing][4].c_str());
			background.b = atoi(mapData[processing][5].c_str());
			isStory = true;
			
		}
		else if (mapData[processing][0] == "DIALOG")
		{
			dialog = mapData[processing][1];
			name = mapData[processing][2];
			setFont(atoi(mapData[processing][3].c_str()));
			background.r = atoi(mapData[processing][4].c_str());
			background.g = atoi(mapData[processing][5].c_str());
			background.b = atoi(mapData[processing][6].c_str());
			background.a = 50;
			textBox.setFillColor(background);
			background.a = 255;
			textBox.setOutlineColor(background);

			textColor.r = atoi(mapData[processing][7].c_str());
			textColor.g = atoi(mapData[processing][8].c_str());
			textColor.b = atoi(mapData[processing][9].c_str());
			textName.setColor(textColor);
			textDialog.setColor(textColor);
			textDialog2.setColor(textColor);

			textName.setString(name);
			textDialog.setString(dialog.substr(0, 1));
			textDialog2.setString("");

			isStory = true;
			countdown = 100;
			textNum = dialog.length();
			textNow = 0;
		}
		//spawning a specific enemy with objective
		else if (mapData[processing][0] == "ENEMY")
		{
			target = sf::Vector2f(atoi(mapData[processing][3].c_str()), atoi(mapData[processing][4].c_str()));
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
		else if (mapData[processing][0] == "OBJECTIVE")
		{
			if (mapData[processing][2] == "TOOL")
			{
			}
			else if (mapData[processing][2] == "DIALOG")
			{
			}
			else if (mapData[processing][2] == "END")
			{
			}
		}
		else if (mapData[processing][0] == "PICTURE")
		{
			processing++;
		}
	}
}

void Story::render(sf::RenderWindow& window)
{
	window.draw(textBox);

	window.draw(textName);
	window.draw(textDialog);
	window.draw(textDialog2);
}

void Story::setFont(int num)
{
	switch (num)
	{
	case 1:
		textDialog.setFont(fontFriend);
		textDialog2.setFont(fontFriend);
		textName.setFont(fontFriend);
		break;
	case 2:
		textDialog.setFont(fontEnemy);
		textDialog2.setFont(fontEnemy);
		textName.setFont(fontEnemy);
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
