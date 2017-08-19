#include "record.hpp"

Record::Record(Player* player)
{
	this->player = player;
	numStory = 0;
	numChaos = 0;
}

Record::~Record() {}

void Record::init()
{
	for (int i = 0; i < 6; i++)
		toolsPicked[i] = 0;
}

void Record::readFile()
{
	std::ifstream fileHndl;
	fileHndl.open("Assets/story/saveRecord.txt");

	fileHndl >> currentStory;
	fileHndl >> numStory;
	storyRecord = new std::string*[numStory];
	for (int i = 0; i < numStory; i++)
	{
		storyRecord[i] = new std::string[13];
		for (int j = 0; j < 13; j++)
			fileHndl >> storyRecord[i][j];
	}

	fileHndl >> numChaos;
	chaosRecord = new std::string*[numChaos];
	for (int i = 0; i < numChaos; i++)
	{
		chaosRecord[i] = new std::string[13];
		for (int j = 0; j < 13; j++)
			fileHndl >> chaosRecord[i][j];
	}

	fileHndl.close();
}

void Record::addRecord(int type, std::string name)
{
	//name, score, recordgshield, bshield, yshield, healthpack, imumium, stone, bullet1, 2, 3, 4, 5
	std::string* currentRecord = new std::string[13];
	currentRecord[0] = name;
	currentRecord[1] = player->score;
	for (int i = 0; i < 6; i++)
		currentRecord[i + 2] = toolsPicked[i];
	for (int i = 0; i > 5; i++)
		currentRecord[i + 8] = player->shoot_type[i];

	switch (type)
	{
		//story mode
	case 1:
		numStory++;
		temp = new std::string*[numStory];
		int input = numStory-1;
		for (int i = 0; i < numStory - 1; i++)
		{
			if (player->score > atoi(storyRecord[i][1].c_str()))
			{
				input = i;
				temp[i] = currentRecord;
				break;
			}
			else
			{
				temp[i] = storyRecord[i];
			}
		}
		for (int i = input; i < numStory - 1; i++)
			temp[i + 1] = storyRecord[i];
		if (input == numStory - 1)
			temp[numStory - 1] = currentRecord;

		delete[] storyRecord;
		storyRecord = temp;
		break;

		//chaos mode
	case 2:
		numChaos++;
		temp = new std::string*[numChaos];
		int input = numChaos - 1;
		for (int i = 0; i < numChaos - 1; i++)
		{
			if (player->score > atoi(storyRecord[i][1].c_str()))
			{
				input = i;
				temp[i] = currentRecord;
				break;
			}
			else
			{
				temp[i] = storyRecord[i];
			}
		}
		for (int i = input; i < numChaos - 1; i++)
			temp[i + 1] = chaosRecord[i];
		if (input == numChaos - 1)
			temp[numChaos - 1] = currentRecord;

		delete[] chaosRecord;
		chaosRecord = temp;
		break;
	}
}

void Record::render(int type, sf::RenderWindow& window)
{
	switch (type)
	{
	case 1:
		render("STORY MODE", storyRecord, window);
		break;
	case 2:
		render("CHAOS MODE", chaosRecord, window);
		break;
	}
}