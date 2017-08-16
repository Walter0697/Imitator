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
}

void Story::setup()
{
}

void Story::update(sf::Time& delta_time)
{
	if (countdown > 0)
		countdown -= delta_time.asMilliseconds();

	if (countdown <= 0 && !isStory)
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
			//text font in [3]
			background.r = atoi(mapData[processing][4].c_str());
			background.g = atoi(mapData[processing][5].c_str());
			background.b = atoi(mapData[processing][6].c_str());
			background.a = atoi(mapData[processing][7].c_str());

			textColorOne.r = atoi(mapData[processing][8].c_str());
			textColorOne.g = atoi(mapData[processing][9].c_str());
			textColorOne.b = atoi(mapData[processing][10].c_str());
			textColorOne.a = atoi(mapData[processing][11].c_str());
		}
		else if (mapData[processing][0] == "ENEMY")
		{
		}
		else if (mapData[processing][0] == "SPAWN")
		{
			for (int i = 0; i < atoi(mapData[processing][2].c_str()); i++)
			{
				//this->enemySet->spawn(atoi(mapData[processing][1].c_str()), );
			}
		}
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

void Story::action(std::string order)
{

}

void Story::clearFile()
{
}
