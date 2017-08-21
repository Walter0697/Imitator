#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"

Game::Game()
{
	//setting up MVC
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);

	std::srand(std::time(0));

	//delete that later
	this->view->menu->unlock();
	for (int i = 1; i < NUM_OF_TOOLS + 1; i++)
		this->model->droprate->unlock(i);

	//adding the updateable objects to the list
	this->model->updateables.push_back(this->model->player);
	this->model->updateables.push_back(this->model->playerSet);
	this->model->updateables.push_back(this->model->enemySet);
	this->model->updateables.push_back(this->model->enemyBulletSet);
	this->model->updateables.push_back(this->model->toolSet);

	//adding the renderable objects to the list
	this->view->renderables.push_back(this->model->radShield);
	this->view->renderables.push_back(this->model->shield);
	this->view->renderables.push_back(this->model->toolSet);
	this->view->renderables.push_back(this->model->playerSet);
	this->view->renderables.push_back(this->model->enemyBulletSet);
	this->view->renderables.push_back(this->model->enemySet);
	this->view->renderables.push_back(this->model->player);	

	//adding the foreground objects to the list
	this->view->foreground.push_back(this->view->hud);
	this->view->foreground.push_back(this->view->enemyhud);
}

Game::~Game()
{ }


void Game::loop()
{

	sf::Time delta_time;

	while (this->view->window.isOpen())
	{
		//get the time since the last time clokc was consulted
		delta_time = this->clock.restart();

		//clear the window before it started
		this->view->window.clear(sf::Color::Black);

		switch (model->gamemode)
		{
		case MODE_STORY_MODE:
			if (this->model->story->isStory)
				this->controller->storyinput(delta_time);
			this->controller->inputs(delta_time);
			if (!this->model->pause)
			{
				if (!this->model->story->isStory)
				{
					this->model->update(delta_time);
					this->model->updateGame(delta_time);
				}
				this->model->updateStory(delta_time);
			}
			this->view->render();
			this->view->renderStory();
			break;

		case MODE_SCORE_BOARD:
			this->controller->scoreinput();
			this->view->renderScore();
			break;

		case MODE_MENU_SCREEN:
			this->controller->menuinput(delta_time, this->view->window);
			this->view->renderMenu();
			break;

		case MODE_REWARDS_MODE:
			this->view->renderMenu();
			break;

		case MODE_CHAOS_MODE:
			this->controller->inputs(delta_time);
			if (!this->model->pause)
			{
				this->model->updateChoas(delta_time);
				this->model->update(delta_time);
				this->model->updateGame(delta_time);
			}
			this->view->render();
			break;

		case MODE_CUSTOM_MODE:
			this->controller->testerinputs(delta_time);
			this->controller->inputs(delta_time);
			if (!this->model->pause)
			{
				this->model->update(delta_time);
				this->model->updateGame(delta_time);
			}
			this->view->render(); 
			break;

		case MODE_GAME_OVER:
			this->controller->menuinput(delta_time, this->view->window);
			this->model->update(delta_time);
			this->view->render();
			this->view->menu->changeScore(this->model->player->score);
			this->view->renderMenu();
			break;
		}	

		//display the game
		this->view->window.display();
	}

	this->view->window.close();
}