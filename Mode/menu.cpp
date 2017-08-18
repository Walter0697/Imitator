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
	unselectedText[0].setString("STORY MODE");
	unselectedText[1].setString("CHAOS MODE");
	unselectedText[2].setString("CUSTOM MODE");
	unselectedText[3].setString("SETTING");
	unselectedText[4].setString("EXIT");

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

void Menu::changeSelect(int num)
{
	switch (num)
	{
	case 1:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 310);
		selectedText.setString("STORY MODE");
		break;
	case 2:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 390);
		selectedText.setString("CHOAS MODE");
		break;
	case 3:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 470);
		selectedText.setString("CUSTOM MODE");
		break;
	case 4:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 550);
		selectedText.setString("SETTING");
		break;
	case 5:
		selectedText.setPosition(SCREEN_WIDTH - title.getLocalBounds().width + 10, 630);
		selectedText.setString("EXIT");
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
	for (int i = 0; i < MENU_OPTION; i++)
		window.draw(unselectedText[i]);
	
}