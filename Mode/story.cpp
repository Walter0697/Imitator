#include "story.hpp"
using namespace std;


Story::Story(EnemySet* enemySet, ToolSet* toolSet, DropRate* droprate, Player* player)
{
	this->enemySet = enemySet;
	this->toolSet = toolSet;
	this->droprate = droprate;
	this->player = player;

	//initialization
	background = sf::Color(0, 0, 0, 50);
	textColor = sf::Color(0, 0, 0, 255);
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

	textMission.setFont(fontVictory);
	textMission.setCharacterSize(40);
	textMission.setColor(sf::Color::Yellow);
	textMission.setStyle(sf::Text::Bold);
	textMission.setString("MISSION");
	textMission.setPosition(SCREEN_WIDTH / 2 - textMission.getLocalBounds().width - 25, -100);

	textComplete = textMission;
	textComplete.setString("COMPLETE");
	textComplete.setPosition(SCREEN_WIDTH / 2 + 15, -100);

	textScore = textComplete;
	textScore.setCharacterSize(30);
	textScore.setString("SCORE:");
	textScore.setPosition(-300, SCREEN_HEIGHT / 2);	
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

	for (int i = 0; i < dataCols; i++)
	{
		for (int j = 0; j < dataRows[i]; j++)
		{
			cout << mapData[i][j] << "  ";
		}
		cout << endl;
	}

	init();
	enemySet->initEnemy();
}

void Story::init()
{
	processing = 0;
	countdown = 0;
	enemyInfo = 0;
	canContin = true;
	isStory = false;

	textMission.setPosition(SCREEN_WIDTH / 2 - textMission.getLocalBounds().width - 25, -100);
	textComplete.setPosition(SCREEN_WIDTH / 2 + 15, -100);
	textScore.setPosition(-900, SCREEN_HEIGHT / 2);
}

void Story::setup(int current)
{
	if (mapData != 0)
		clearFile();

	switch (current)
	{
	case 1:
		if (readStory >= 1)
			readFile("Assets/story/story_01_finish.txt");
		else
			readFile("Assets/story/story_01.txt");
		break;
	case 2:
		if (readStory >= 2)
			readFile("Assets/story/story_02_finish.txt");
		else
			readFile("Assets/story/story_02.txt");
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

	//just wait
	if (isWait)
	{
		if (countdown <= 0)
		{
			isWait = false;
			processing++;
		}
	}

	if (enemyInfo != 0 && countdownEnd == -1)
	{
		if (countdown <= 0)
		{
			enemySet->spawn(rand() % spawntype + spawnend, rand() % SCREEN_WIDTH);
			countdown += countdownMax;
		}
	}

	//stop target enemy
	if (enemyInfo != 0 && target.x != -1)
	{
		if (enemyInfo->position.y >= target.y)
			enemyInfo->velocity = sf::Vector2f(0, 0);
	}

	//after data read
	if (isStory)
	{
		//rendering dialog
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
				else if (line == 2 || dialog2 == "NULL")
				{
					countdown += 150;
					textNow = 0;
					textNum = 100;
					line = 3;
				}
			}
			if (line == 3)
			{
				canContin = true;
				sprite_enter.setPosition(SCREEN_WIDTH - 97, SCREEN_HEIGHT - 114);
			}

			if (line == 1)
				textDialog.setString(dialog.substr(0, textNow));
			else if (line == 2)
				textDialog2.setString(dialog2.substr(0, textNow));
		}
		//rendering cutscene
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
		//rendering victory
		else if (mapData[processing][0] == "VICTORY")
		{
			while (countdown <= 0 && line == 1)
			{
				textMission.setPosition(textMission.getPosition().x, textMission.getPosition().y + 5);
				countdown += 10;
			}
			while (countdown <= 0 && line == 2)
			{
				textComplete.setPosition(textComplete.getPosition().x, textComplete.getPosition().y + 5);
				countdown += 10;
			}
			while (countdown <= 0 && line == 3)
			{
				textScore.setPosition(textScore.getPosition().x,  textScore.getPosition().y + 5);
				countdown += 5;
			}

			if (textMission.getPosition().y >= 350 && line == 1)
				line = 2;
			else if (textComplete.getPosition().y >= 350 && line == 2)
				line = 3;
			else if (textScore.getPosition().y >= SCREEN_HEIGHT / 2 && line == 3)
			{
				line = 4;
				canContin = true;
			}
		}
	}

	//read the data if haven't
	else if (!isWait && !isStory && processing < dataCols)
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
			if (atoi(mapData[processing][1].c_str()) < 90)
			{
				target = sf::Vector2f(atoi(mapData[processing][2].c_str()), atoi(mapData[processing][3].c_str()));
				targetEnemy(atoi(mapData[processing][1].c_str()), atoi(mapData[processing][2].c_str()));
			}
			else
			{
				target = sf::Vector2f(-1, -1);
				targetEnemy(atoi(mapData[processing][1].c_str()), -1);
			}

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
			isWait = true;
		}
		//rewards after killing target
		else if (mapData[processing][0] == "OBJECTIVE")
		{
			if (enemySet->checkOutOfBound(*enemyInfo) && enemyInfo != 0)
			{
				if (countdownEnd == -1)
					countdownEnd = 0;
				enemyInfo = 0;
				processing++;
			}
		}
		//dropping tools
		else if (mapData[processing][0] == "TOOL")
		{
			dropTool(atoi(mapData[processing][1].c_str()), atoi(mapData[processing][2].c_str()), atoi(mapData[processing][3].c_str()));
			processing++;
		}
		//to unlock a tool
		else if (mapData[processing][0] == "UNLOCK")
		{
			toolUnlock = atoi(mapData[processing][1].c_str());
			this->droprate->unlock(toolUnlock);
			processing++;
		}
		//show picture
		else if (mapData[processing][0] == "PICTURE")
		{
			spriteAppear(atoi(mapData[processing][1].c_str()),
						atoi(mapData[processing][2].c_str()), atoi(mapData[processing][3].c_str()) );
			processing++;
		}
		//show picture ended
		else if (mapData[processing][0] == "PICTUREEND")
		{
			spriteAppear(atoi(mapData[processing][1].c_str()), 99999, 99999);
			processing++;
		}
		//just victory
		else if (mapData[processing][0] == "VICTORY")
		{
			textMission.setPosition(textMission.getPosition().x, -100);
			textComplete.setPosition(textComplete.getPosition().x, -100);
			textScore.setString("CURRENT SCORE:" + std::to_string(player->score));
			textScore.setPosition(SCREEN_WIDTH / 2 - textScore.getLocalBounds().width / 2, -100);

			isStory = true;
			canContin = false;
			countdown = 0;
			line = 1;
		}
		//randomly spawn
		else if (mapData[processing][0] == "RSPAWN")
		{
			if (countdownEnd == 0)
			{
				spawntype = atoi(mapData[processing][1].c_str());
				spawnend = atoi(mapData[processing][2].c_str());
				countdown = atoi(mapData[processing][3].c_str());
				countdownMax = countdown;
				countdownEnd = atoi(mapData[processing][4].c_str());
			}
			else if (countdownEnd == -1)
			{
				processing++;
			}
			else
			{
				countdownEnd -= delta_time.asMilliseconds();
				if (countdown <= 0)
				{
					countdown += countdownMax;
					enemySet->spawn(rand() % spawntype + spawnend, rand() % SCREEN_WIDTH);
					if (countdownEnd <= 0)
					{
						countdownMax = 0;
						countdownEnd = 0;
						processing++;
					}
				}
			}
		}
	}
}

void Story::spriteAppear(int type, int positionx, int positiony)
{
	sprite[type - 1].setPosition(positionx, positiony);
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
	case 5:
		toolSet->imumium[toolSet->availableTool(5)].velocity.y = toolSet->imumium[0].speed;
		toolSet->imumium[toolSet->availableTool(5)].position = sf::Vector2f(positionx, positiony);
		break;
	case 6:
		toolSet->stoneTool[toolSet->availableTool(6)].velocity.y = toolSet->stoneTool[0].speed;
		toolSet->stoneTool[toolSet->availableTool(6)].position = sf::Vector2f(positionx, positiony);
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
			if (canContin)
				window.draw(sprite_enter);
		}
		else if (mapData[processing][0] == "VICTORY" && isStory)
		{
			window.draw(textMission);
			window.draw(textComplete);
			window.draw(textScore);
		}
	}
	for (int i = 0; i < 3; i++)
		window.draw(sprite[i]);
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
		textDialog.setFont(fontFriend2);
		textDialog2.setFont(fontFriend2);
		textName.setFont(fontFriend2);
		textCutScene.setFont(fontFriend2);
		break;
	case 3:
		textDialog.setFont(fontEnemy);
		textDialog2.setFont(fontEnemy);
		textName.setFont(fontEnemy);
		textCutScene.setFont(fontEnemy);
		break;
	case 4:
		textDialog.setFont(fontEnemy2);
		textDialog2.setFont(fontEnemy2);
		textName.setFont(fontEnemy2);
		textCutScene.setFont(fontEnemy2);
		break;
	case 5:
		textDialog.setFont(fontUnknown);
		textDialog2.setFont(fontUnknown);
		textName.setFont(fontUnknown);
		textCutScene.setFont(fontUnknown);
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
	case 91:
		enemyInfo = &enemySet->boss_devplane;
		enemySet->spawn(1);
		break;
	case 92:
		enemyInfo = &enemySet->boss_modifier;
		enemySet->spawn(2);
		break;
	case 93:
		enemyInfo = &enemySet->boss_firethrower;
		enemySet->spawn(3);
		break;
	case 94:
		enemyInfo = &enemySet->boss_alien;
		enemySet->spawn(4);
		break;
	case 95:
		enemyInfo = &enemySet->boss_labplane;
		enemySet->spawn(5);
		break;
	case 96:
		enemyInfo = &enemySet->boss_final;
		enemySet->spawn(6);
		break;
	}
	if (x_position != -1)
	{
		enemyInfo->position = sf::Vector2f(x_position, -80);
		enemyInfo->velocity.y = enemyInfo->speed;
		enemyInfo->shoot_count = 0;
	}
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
