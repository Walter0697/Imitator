#include "menu.hpp"

Menu::Menu()
{
	
}

Menu::~Menu() {}

void Menu::setup()
{
	title.setFont(font);
	title.setString("IMITATOR              ");
	title.setCharacterSize(60);
	title.setPosition(SCREEN_WIDTH - title.getLocalBounds().width, 100);
	title.setColor(sf::Color::White);
	title.setStyle(sf::Style::Default);

	for (int i = 0; i < MENU_OPTION; i++)
	{
		unselectedText[i] = title;
		unselectedText[i].setFont(font2);
		unselectedText[i].setCharacterSize(40);
		unselectedText[i].setPosition(SCREEN_WIDTH - title.getLocalBounds().width, 300 + (80) * i);
	}

	selectBar[0] = "STORY MODE";
	selectBar[1] = "CHAOS MODE";
	selectBar[2] = "SCOREBOARD";
	selectBar[3] = "CONTROL";
	selectBar[4] = "EXIT";
	selectBar[5] = " ";

	for (int i = 0; i < MENU_OPTION; i++)
		unselectedText[i].setString(selectBar[i]);

	for (int i = 0; i < 3; i++)
	{
		storyText[i] = unselectedText[0];
		storyText[i].setCharacterSize(35);
	}

	storyText[0].setString("CONTINUE");
	storyText[0].setPosition(450, 340);
	storyText[1].setString("NEW GAME");
	storyText[1].setPosition(450, 400);
	storyText[2].setString("BACK");
	storyText[2].setPosition(450, 460);

	selectedText = unselectedText[0];
	selectedText.setColor(sf::Color::Cyan);
	selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 310);
	selectedText.setString("STORY MODE");

	gameOverText = selectedText;
	gameOverText.setColor(sf::Color::Red);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(SCREEN_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, 310);

	scoreText = gameOverText;
	scoreText.setString("SCORE : ");
	scoreText.setCharacterSize(20);
	
	restartText = scoreText;
	restartText.setString("Press R to go back to menu");
	restartText.setPosition(SCREEN_WIDTH / 2 - restartText.getLocalBounds().width / 2, 600);

	menuplayer.setPosition(500, 500);
}

void Menu::unlock()
{
	newModeUnlock = true;
	selectBar[0] = "STORY MODE";
	selectBar[1] = "CHAOS MODE";
	selectBar[2] = "CUSTOM MODE";
	selectBar[3] = "SCOREBOARD";
	selectBar[4] = "CONTROL";
	selectBar[5] = "EXIT";

	for (int i = 0; i < MENU_OPTION; i++)
		unselectedText[i].setString(selectBar[i]);
}

void Menu::changeSelect(int num)
{
	switch (num)
	{
	case 1:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 310);
		selectedText.setString(selectBar[0]);
		break;
	case 2:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 390);
		selectedText.setString(selectBar[1]);
		break;
	case 3:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 470);
		selectedText.setString(selectBar[2]);
		break;
	case 4:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 550);
		selectedText.setString(selectBar[3]);
		break;
	case 5:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 630);
		selectedText.setString(selectBar[4]);
		break;
	case 6:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 710);
		selectedText.setString(selectBar[5]);
		break;
	case 7:
		selectedText.setPosition(460, 350);
		selectedText.setString("CONTINUE");
		break;
	case 8:
		selectedText.setPosition(460, 410);
		selectedText.setString("NEW GAME");
		break;
	case 9:
		selectedText.setPosition(460, 470);
		selectedText.setString("BACK");
		break;
	}
}

void Menu::changeScore(int score)
{
	scoreText.setString("SCORE : " + std::to_string(score));
	scoreText.setPosition(SCREEN_WIDTH / 2 - scoreText.getLocalBounds().width / 2, 500);
}

void Menu::renderGameOver(sf::RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(scoreText);
	window.draw(restartText);
}

void Menu::render(sf::RenderWindow& window) 
{
	window.draw(menuplayer);
	window.draw(title);
	window.draw(selectedText);
	if (this->newModeUnlock)
		for (int i = 0; i < MENU_OPTION; i++)
			window.draw(unselectedText[i]);
	else
		for (int i = 0; i < 5; i++)
			window.draw(unselectedText[i]);

	if (storyClicked)
		for (int i = 0; i < 3; i++)
			window.draw(storyText[i]);
	
}