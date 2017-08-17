#include "story.hpp"
using namespace std;


Story::Story(EnemySet* enemySet)
{
	this->enemySet = enemySet;

	background = sf::Color(0, 0, 0, 255);
	textColorOne = sf::Color(0, 0, 0, 255);
	textColorTwo = sf::Color(0, 0, 0, 255);

	readFile("Assets/story/story_01.txt");

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

	//set up sf::text
}

void Story::setup(int current)
{
}

void Story::update(sf::Time& delta_time)
{
	//countdown
	if (countdown > 0)
		countdown -= delta_time.asMilliseconds();

	//after data read
	if (isStory)
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
			//text font in [2]
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
			background.a = atoi(mapData[processing][7].c_str());

			textColorOne.r = atoi(mapData[processing][8].c_str());
			textColorOne.g = atoi(mapData[processing][9].c_str());
			textColorOne.b = atoi(mapData[processing][10].c_str());
			textColorOne.a = atoi(mapData[processing][11].c_str());

			isStory = true;
			countdown = 100;
			textNum = dialog.length();
			textNow = 0;

			//set up sf::text
		}
		//spawning a specific enemy with objective
		else if (mapData[processing][0] == "ENEMY")
		{
			target = sf::Vector2f(atoi(mapData[processing][3].c_str()), atoi(mapData[processing][4].c_str()));
			targetEnemy(atoi(mapData[processing][1].c_str()), atoi(mapData[processing][2].c_str()));
		}
		//spawning a group of enemies
		else if (mapData[processing][0] == "SPAWN")
		{
			int num = atoi(mapData[processing][2].c_str());
			for (int i = 0; i < num; i++)
			{
				this->enemySet->spawn(atoi(mapData[processing][1].c_str()), (i+1.f)/(num+1.f) * SCREEN_WIDTH);
			}
		}
		//setting up countdown time to wait
		else if (mapData[processing][0] == "WAIT")
		{
			countdown = atoi(mapData[processing][1].c_str());
		}
		else if (mapData[processing][0] == "OBJECTIVE")
		{
		
		}
		else if (mapData[processing][0] == "PICTURE")
		{
		
		}
	}
}

void Story::render(sf::RenderWindow& window)
{
}

void Story::setFont(int num)
{
	switch (num)
	{
	case 1:
		textDialog.setFont(fontFriend);
		textName.setFont(fontFriend);
		break;
	case 2:
		textDialog.setFont(fontEnemy);
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
