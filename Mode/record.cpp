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

void Record::setup()
{
	titleText.setFont(font);
	titleText.setCharacterSize(40);
	titleText.setPosition(230, 30);
	titleText.setColor(sf::Color::White);
	titleText.setStyle(sf::Style::Default);
	titleText.setString("STORY MODE");

	recordText = titleText;
	recordText.setColor(sf::Color::Black);
	recordText.setCharacterSize(20);
	recordText.setStyle(sf::Text::Bold);

	currentRank = -1;
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
		currentRank = numStory-1;
		for (int i = 0; i < numStory - 1; i++)
		{
			if (player->score > atoi(storyRecord[i][1].c_str()))
			{
				currentRank = i;
				temp[i] = currentRecord;
				break;
			}
			else
			{
				temp[i] = storyRecord[i];
			}
		}
		for (int i = currentRank; i < numStory - 1; i++)
			temp[i + 1] = storyRecord[i];
		if (currentRank == numStory - 1)
			temp[numStory - 1] = currentRecord;

		delete[] storyRecord;
		storyRecord = temp;
		break;

		//chaos mode
	case 2:
		numChaos++;
		temp = new std::string*[numChaos];
		currentRank = numChaos - 1;
		for (int i = 0; i < numChaos - 1; i++)
		{
			if (player->score > atoi(storyRecord[i][1].c_str()))
			{
				currentRank = i;
				temp[i] = currentRecord;
				break;
			}
			else
			{
				temp[i] = storyRecord[i];
			}
		}
		for (int i = currentRank; i < numChaos - 1; i++)
			temp[i + 1] = chaosRecord[i];
		if (currentRank == numChaos - 1)
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
		render("STORY MODE", numStory, storyRecord, window);
		break;
	case 2:
		render("CHAOS MODE", numChaos, chaosRecord, window);
		break;
	}
}

void Record::render(std::string title, int num, std::string** recordInfo, sf::RenderWindow& window)
{
	window.draw(scoreBoard);

	titleText.setString(title);
	window.draw(titleText);

	if (shouldRender > numStory)
		shouldRender = numStory;

	currenty = 200;
	for (int i = 0; i < shouldRender; i++)
	{
		currentx = 35;
		renderString(currentx, currenty, std::to_string(i + 1), window);
		currentx = 100;
		renderString(currentx, currenty, recordInfo[i][0], window);
		currentx = 190;
		renderString(currentx, currenty, recordInfo[i][1], window);
		currentx = 330;
		renderString(currentx, currenty, recordInfo[i][2], window);
		currentx = 365;
		renderString(currentx, currenty, recordInfo[i][3], window);
		currentx = 400;
		renderString(currentx, currenty, recordInfo[i][4], window);
		currentx = 435;
		renderString(currentx, currenty, recordInfo[i][5], window);
		currentx = 470;
		renderString(currentx, currenty, recordInfo[i][6], window);
		currentx = 515;
		renderString(currentx, currenty, recordInfo[i][7], window);
		
		currentx = 565;
		for (int j = 0; j < 5; j++)
		{
			if (atoi(recordInfo[i][j + 8].c_str()) != 0)
			{
				bullet_sprite[atoi(recordInfo[i][j + 8].c_str()) - 1].setPosition(currentx, currenty);
				window.draw(bullet_sprite[atoi(recordInfo[i][j + 8].c_str()) - 1]);
				currentx += 40;
			}
		}
		currenty += 70;
	}

	if (currentRank != -1)
	{
		currentx = 35; currenty = 915;
		renderString(currentx, currenty, std::to_string(currentRank + 1), window);
		currentx = 100;
		renderString(currentx, currenty, "CURRENT RECORD", window);
		currentx = 190;
		renderString(currentx, currenty, std::to_string(player->score), window);
		currentx = 330;
		renderString(currentx, currenty, std::to_string(toolsPicked[0]), window);
		currentx = 365;
		renderString(currentx, currenty, std::to_string(toolsPicked[1]), window);
		currentx = 400;
		renderString(currentx, currenty, std::to_string(toolsPicked[2]), window);
		currentx = 435;
		renderString(currentx, currenty, std::to_string(toolsPicked[3]), window);
		currentx = 470;
		renderString(currentx, currenty, std::to_string(toolsPicked[4]), window);
		currentx = 515;
		renderString(currentx, currenty, std::to_string(toolsPicked[5]), window);
		currentx = 565;
		for (int i = 0; i < 5; i++)
			if (player->shoot_type[i] != 0)
			{
				bullet_sprite[player->shoot_type[i] - 1].setPosition(currentx, currenty);
				window.draw(bullet_sprite[player->shoot_type[i] - 1]);
				currentx += 40;
			}
	}
}

void Record::renderString(int positionx, int positiony, std::string text, sf::RenderWindow& window)
{
	recordText.setString(text);
	recordText.setPosition(positionx, positiony);
	window.draw(recordText);
}