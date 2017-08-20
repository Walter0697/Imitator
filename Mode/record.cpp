#include "record.hpp"

Record::Record(Player* player, Story* story)
{
	this->player = player;
	this->story = story;
	numStory = 0;
	numChaos = 0;

	readFile();
}

Record::~Record() {}

void Record::init()
{
	for (int i = 0; i < 6; i++)
		toolsPicked[i] = 0;

	if (temp != 0)
	{
		delete[] temp;
		temp = 0;
	}
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
	currentType = -1;
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

void Record::writeFile()
{
	std::ofstream fileWriter;
	fileWriter.open("Assets/story/saveRecord.txt");
	fileWriter << story->currentStory << "\n";

	fileWriter << numStory << "\n";
	for (int i = 0; i < numStory; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			fileWriter << storyRecord[i][j] << " ";
		}
		fileWriter << "\n";
	}

	fileWriter << numChaos << "\n";
	for (int i = 0; i < numChaos; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			fileWriter << chaosRecord[i][j] << " ";
		}
		fileWriter << "\n";
	}
	fileWriter.close();
}

void Record::addRecord(int type, std::string name)
{
	//name, score, recordgshield, bshield, yshield, healthpack, imumium, stone, bullet1, 2, 3, 4, 5
	std::string* currentRecord = new std::string[13];
	currentRecord[0] = name;
	currentRecord[1] = std::to_string(player->score);
	for (int i = 0; i < 6; i++)
		currentRecord[i + 2] = std::to_string(toolsPicked[i]);
	for (int i = 0; i < 5; i++)
		currentRecord[i + 8] = std::to_string(player->shoot_type[i]);

	currentType = type;

	switch (type)
	{
		//story mode
	case 1:
		numStory++;
		temp = new std::string*[numStory];
		currentRank = numStory - 1;
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
			if (player->score > atoi(chaosRecord[i][1].c_str()))
			{
				currentRank = i;
				temp[i] = currentRecord;
				break;
			}
			else
			{
				temp[i] = chaosRecord[i];
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
	writeFile();
}

void Record::render(int type, sf::RenderWindow& window)
{
	shouldRender = 10;
	switch (type)
	{
	case 1:
		render("STORY MODE", 1, storyRecord, window);
		break;
	case 2:
		render("CHAOS MODE", 2, chaosRecord, window);
		break;
	}
}

void Record::render(std::string title, int num, std::string** recordInfo, sf::RenderWindow& window)
{
	window.draw(scoreBoard);

	titleText.setString(title);
	titleText.setPosition(SCREEN_WIDTH / 2 - titleText.getLocalBounds().width / 2, titleText.getPosition().y);
	window.draw(titleText);

	switch (num)
	{
	case 1:
		if (shouldRender > numStory)
		{
			shouldRender = numStory; 
		}
		break;
	case 2:
		if (shouldRender > numChaos)
		{
			shouldRender = numChaos;
		}
		break;
	}

	currentx = 35;
	currenty = 150;
	renderString(currentx, currenty, "NO.", window);
	currentx = 100;
	renderString(currentx, currenty, "NAME", window);
	currentx = 225;
	renderString(currentx, currenty, "SCORE", window);
	currentx = 565;
	renderString(currentx, currenty, "BULLET TYPE", window);

	currenty = 200;
	for (int i = 0; i < shouldRender; i++)
	{
		currentx = 35;
		renderString(currentx, currenty, std::to_string(i + 1), window);
		currentx = 100;
		renderString(currentx, currenty, recordInfo[i][0], window);
		currentx = 225;
		renderString(currentx, currenty, recordInfo[i][1], window);
		currentx = 340;
		renderString(currentx, currenty, recordInfo[i][2], window);
		currentx = 375;
		renderString(currentx, currenty, recordInfo[i][3], window);
		currentx = 410;
		renderString(currentx, currenty, recordInfo[i][4], window);
		currentx = 445;
		renderString(currentx, currenty, recordInfo[i][5], window);
		currentx = 485;
		renderString(currentx, currenty, recordInfo[i][6], window);
		currentx = 525;
		renderString(currentx, currenty, recordInfo[i][7], window);
		
		currentx = 570;
		currenty -= 20;
		for (int j = 0; j < 5; j++)
		{
			if (atoi(recordInfo[i][j + 8].c_str()) != 0)
			{
				bullet_sprite[atoi(recordInfo[i][j + 8].c_str()) - 1].setPosition(currentx, currenty);
				window.draw(bullet_sprite[atoi(recordInfo[i][j + 8].c_str()) - 1]);
			}
			currentx += 35;
			currenty += 4;
		}
		currenty += 50;
	}

	if (currentRank != -1 && currentType == num)
	{
		currentx = 35; currenty = 915;
		renderString(currentx, currenty, std::to_string(currentRank + 1), window);
		currentx = 100;
		renderString(currentx, currenty, "CURRENT", window);
		currentx = 225;
		renderString(currentx, currenty, std::to_string(player->score), window);
		currentx = 340;
		renderString(currentx, currenty, std::to_string(toolsPicked[0]), window);
		currentx = 375;
		renderString(currentx, currenty, std::to_string(toolsPicked[1]), window);
		currentx = 410;
		renderString(currentx, currenty, std::to_string(toolsPicked[2]), window);
		currentx = 445;
		renderString(currentx, currenty, std::to_string(toolsPicked[3]), window);
		currentx = 485;
		renderString(currentx, currenty, std::to_string(toolsPicked[4]), window);
		currentx = 525;
		renderString(currentx, currenty, std::to_string(toolsPicked[5]), window);
		
		currentx = 570;
		currenty -= 20;
		for (int i = 0; i < 5; i++)
		{
			if (player->shoot_type[i] != 0)
			{
				bullet_sprite[player->shoot_type[i] - 1].setPosition(currentx, currenty);
				window.draw(bullet_sprite[player->shoot_type[i] - 1]);
			}
			currentx += 35;
			currenty += 4;
		}
	}
}

void Record::renderString(int positionx, int positiony, std::string text, sf::RenderWindow& window)
{
	recordText.setString(text);
	recordText.setPosition(positionx, positiony);
	window.draw(recordText);
}