#include "controller.hpp"

Controller::Controller(Model* model, View* view)
{
	this->model = model;
	this->view = view;

	selecting = 1;
}

Controller::~Controller() {}

void Controller::storyinput(sf::Time delta_time)
{
	while (this->view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->view->window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Return:
				if (this->model->story->processing < this->model->story->dataCols)
				{
					if (this->model->story->mapData[this->model->story->processing][0] == "DIALOG")
					{
						if (this->model->story->canContin == false)
							this->model->story->countdown -= 75;
						else
						{
							this->model->story->isStory = false;
							this->model->story->processing++;
						}
					}
					else if (this->model->story->mapData[this->model->story->processing][0] == "CUTSCENE")
					{
						if (this->model->story->canContin == false)
							this->model->story->countdown -= 25;
					}
					else if (this->model->story->mapData[this->model->story->processing][0] == "VICTORY")
					{
						if (this->model->story->canContin)
						{
							this->model->story->currentStory++;
							this->model->story->setup(this->model->story->currentStory);
							//initialize bulles
							this->model->playerSet->initBullet();
							this->model->enemyBulletSet->initBullet();
						}
					}
				}
				break;
			}
		}
	}
	if (this->model->story->currentStory == LAST_STORY)
	{
		this->view->menu->unlock();
		this->model->gamemode = MODE_MENU_SCREEN;
		this->selecting = 1;
	}
}

void Controller::menuinput(sf::Time delta_time, sf::RenderWindow& window)
{
	while (this->view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->view->window.close();
			break;
		
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				this->selecting--;
				if (this->view->menu->storyClicked)
				{
					if (this->selecting == 6)
						this->selecting = 9;
				}
				else if (!this->view->menu->newModeUnlock)
				{
					if (this->selecting == 0)
						this->selecting = 4;
				}
				else if (this->selecting == 0)
						this->selecting = MENU_OPTION;
				break;
			case sf::Keyboard::S:
				this->selecting++;
				if (this->view->menu->storyClicked)
				{
					if (this->selecting == 10)
						this->selecting = 7;
				}
				else if (this->view->menu->newModeUnlock)
				{
					if (this->selecting == MENU_OPTION + 1)
						this->selecting = 1;
				}
				else
				{
					if (this->selecting == 5)
						this->selecting = 1;
				}
				break;
			case sf::Keyboard::R:
				if (this->model->gamemode == MODE_GAME_OVER)
				{	
					this->selecting = 1;
					this->view->scoreboard = this->model->record->currentType;
					this->model->gamemode = MODE_SCORE_BOARD;
				}
				break;
			case sf::Keyboard::F10:
				this->view->menu->unlock();
				selecting = 1;
				break;
			}
			this->view->menu->changeSelect(this->selecting);
			break;

		case sf::Event::MouseMoved:
			this->view->mouse_position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			if (this->view->menu->newModeUnlock)
			{
				if (this->view->menu->storyClicked)
				{
					if ((inOption(event.mouseMove.x, event.mouseMove.y) >= 7 &&
						inOption(event.mouseMove.x, event.mouseMove.y) <= 9) ||
						inOption(event.mouseMove.x, event.mouseMove.y) == 1)
					{
						selecting = inOption(event.mouseMove.x, event.mouseMove.y);
						this->view->menu->changeSelect(this->selecting);
					}
				}
				if (inOption(event.mouseMove.x, event.mouseMove.y) != -1 && inOption(event.mouseMove.x, event.mouseMove.y) < 7)
				{
					selecting = inOption(event.mouseMove.x, event.mouseMove.y);
					this->view->menu->changeSelect(this->selecting);
				}
			}
			else
			{
				if (this->view->menu->storyClicked)
				{
					if ((inOption(event.mouseMove.x, event.mouseMove.y) >= 7 &&
						inOption(event.mouseMove.x, event.mouseMove.y) <= 9) ||
						inOption(event.mouseMove.x, event.mouseMove.y) == 1)
					{
						selecting = inOption(event.mouseMove.x, event.mouseMove.y);
						this->view->menu->changeSelect(this->selecting);
					}
				}
				if (inOption(event.mouseMove.x, event.mouseMove.y) != -1 && inOption(event.mouseMove.x, event.mouseMove.y) < 5)
				{
					selecting = inOption(event.mouseMove.x, event.mouseMove.y);
					this->view->menu->changeSelect(this->selecting);
				}
			}
			break;
		}
	}

	//mouse clicking or pressing return
	if (this->model->gamemode == MODE_MENU_SCREEN)
	{
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return && keyboardClick == false)
		{
			enter();
			keyboardClick = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			keyboardClick = false;

		if (event.type == sf::Event::MouseButtonReleased && isClick == false)
			if (inOption(event.mouseButton.x, event.mouseButton.y) == selecting)
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					enter();
					isClick = true;
				}
		if (event.type == sf::Event::MouseButtonPressed)
			isClick = false;
	}

}

void Controller::scoreinput()
{
	while (this->view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->view->window.close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (this->model->record->startPosition != 0)
					this->model->record->startPosition--;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				switch (this->view->scoreboard)
				{
				case 1:
					if (10 <= this->model->record->numStory)
					{
						if (this->model->record->startPosition != this->model->record->numStory - 10)
							this->model->record->startPosition++;
					}
					break;
				case 2:
					if (10 <= this->model->record->numChaos)
					{
						if (this->model->record->startPosition != this->model->record->numChaos - 10)
							this->model->record->startPosition++;
					}
					break;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				this->model->record->startPosition = 0;
				if (this->view->scoreboard == 1) this->view->scoreboard = 2;
				else this->view->scoreboard = 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				this->view->menu->storyClicked = false;
				this->selecting = 1;
				this->view->menu->changeSelect(1);
				this->model->gamemode = MODE_MENU_SCREEN;
			}
			break;
		}
	}
	if (event.type == sf::Event::MouseMoved)
		this->view->mouse_position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
		

	if (event.type == sf::Event::MouseButtonReleased && isClick == false)
		if ((event.mouseButton.x >= 0 && event.mouseButton.x <= 130 &&
			event.mouseButton.y >= 0 && event.mouseButton.y <= 120) ||
			event.mouseButton.x >= SCREEN_WIDTH - 130 && event.mouseButton.x <= SCREEN_WIDTH &&
			event.mouseButton.y >= 0 && event.mouseButton.y <= 120)
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				this->model->record->startPosition = 0;
				if (this->view->scoreboard == 1) this->view->scoreboard = 2;
				else this->view->scoreboard = 1;
				isClick = true;
			}
	if (event.type == sf::Event::MouseButtonPressed)
		isClick = false;
}

void Controller::enter()
{
	if (this->view->menu->newModeUnlock)
	{
		switch (this->selecting)
		{
		case 1:
			//this->model->story->setup(this->model->story->currentStory);
			//this->model->gamemode = MODE_STORY_MODE;
			this->view->menu->storyClicked = !this->view->menu->storyClicked;
			if (this->view->menu->storyClicked)
				this->selecting = 7;
			else
				this->selecting = 1;

			this->view->menu->changeSelect(this->selecting);
			break;
		case 2:
			this->model->initAll();
			this->model->gamemode = MODE_CHAOS_MODE;
			break;
		case 3:
			this->model->initAll();
			test = 0;
			this->model->gamemode = MODE_CUSTOM_MODE;
			break;
		case 4:
			this->model->record->startPosition = 0;
			this->view->scoreboard = 1;
			this->model->gamemode = MODE_SCORE_BOARD;
			break;
		//case 5:
			//how to play
		case 6:
			this->view->window.close();
			break;
		case 7:
			this->model->initAll();
			this->model->story->setup(this->model->story->currentStory);
			this->model->gamemode = MODE_STORY_MODE;
			break;
		case 8:
			this->model->initAll();
			this->model->story->currentStory = 1;
			this->model->story->setup(this->model->story->currentStory);
			this->model->gamemode = MODE_STORY_MODE;
			break;
		case 9:
			this->view->menu->storyClicked = false;
			this->selecting = 1;
			this->view->menu->changeSelect(this->selecting);
			break;
		}
	}
	//haven't unlock the new mode
	else
	{
		switch (this->selecting)
		{
		case 1:
			this->view->menu->storyClicked = !this->view->menu->storyClicked;
			if (this->view->menu->storyClicked)
				this->selecting = 7;
			else
				this->selecting = 1;

			this->view->menu->changeSelect(this->selecting);
			break;
		case 2:
			this->model->record->startPosition = 0;
			this->view->scoreboard = 1;
			this->model->gamemode = MODE_SCORE_BOARD;
			break;
		//case 3:
			//how to play
		case 4:
			this->view->window.close();
			break;
		case 7:
			this->model->initAll();
			this->model->story->setup(this->model->story->currentStory);
			this->model->gamemode = MODE_STORY_MODE;
			break;
		case 8:
			this->model->initAll();
			this->model->story->currentStory = 1;
			this->model->story->setup(this->model->story->currentStory);
			this->model->gamemode = MODE_STORY_MODE;
			break;
		case 9:
			this->view->menu->storyClicked = false;
			this->selecting = 1;
			this->view->menu->changeSelect(this->selecting);
			break;
		}
	}
}

int Controller::inOption(float positionx, float positiony)
{
	if (positionx >= 100 && positionx <= 500)
	{
		if (positiony >= 310 && positiony <= 360)
			return 1;
		else if (positiony >= 390 && positiony <= 440)
			return 2;
		else if (positiony >= 470 && positiony <= 520)
			return 3;
		else if (positiony >= 550 && positiony <= 600)
			return 4;
		else if (positiony >= 630 && positiony <= 680)
			return 5;
		else if (positiony >= 710 && positiony <= 760)
			return 6;
	}
	else if (positionx >= 450 && positionx <= 780)
	{
		if (positiony >= 340 && positiony <= 380)
			return 7;
		else if (positiony >= 400 && positiony <= 440)
			return 8;
		else if (positiony >= 460 && positiony <= 500)
			return 9;
	}
	return -1;
}

void Controller::inputs(sf::Time delta_time)
{
	while (this->view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->view->window.close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
				if (this->model->story->isStory == false)
					this->model->pause = !this->model->pause;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		this->model->gamemode = MODE_MENU_SCREEN;

	//player shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!this->model->pause)
			this->model->shoot();
	}

	//position changing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->model->player->velocity.x = -this->model->player->speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->model->player->velocity.x = this->model->player->speed;
	}
	else
	{
		this->model->player->velocity.x = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->model->player->velocity.y = -this->model->player->speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->model->player->velocity.y = this->model->player->speed;
	}
	else
	{
		this->model->player->velocity.y = 0;
	}

	//out of bound checking
	if (this->model->player->position.x + this->model->player->velocity.x * delta_time.asSeconds() + this->model->player->size.x >= this->model->screen_br.x)
	{
		this->model->player->position.x = this->model->screen_br.x - this->model->player->speed * delta_time.asSeconds() - this->model->player->size.x;
	}
	else if (this->model->player->position.x + this->model->player->velocity.x * delta_time.asSeconds() <= this->model->screen_tl.x)
	{
		this->model->player->position.x = this->model->screen_tl.x + this->model->player->speed * delta_time.asSeconds();
	}

	if (this->model->player->position.y + this->model->player->velocity.y * delta_time.asSeconds() + this->model->player->size.y >= this->model->screen_br.y)
	{
		this->model->player->position.y = this->model->screen_br.y - this->model->player->speed * delta_time.asSeconds() - this->model->player->size.y;
	}
	else if (this->model->player->position.y + this->model->player->velocity.y * delta_time.asSeconds() <= this->model->screen_tl.y)
	{
		this->model->player->position.y = this->model->screen_tl.y + this->model->player->speed * delta_time.asSeconds();
	}
}

void Controller::testerinputs(sf::Time delta_time)
{
	while (this->view->window.pollEvent(event))
	{
		switch(event.type)
		{
			//for testing only
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					this->model->enemySet->spawn(rand() % 11, rand() % SCREEN_WIDTH);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
					this->view->viewHitBox = !this->view->viewHitBox;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
					this->model->radShield->addShield(5);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					this->model->player->addBullet(1, 1000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
					this->model->player->addBullet(2, 600);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
					this->model->player->addBullet(3, 2000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
					this->model->player->addBullet(4, 1500);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
					this->model->player->addBullet(5, 1500);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
					this->model->player->addBullet(6, 150);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
					this->model->player->addBullet(7, 2000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
					this->model->player->addBullet(8, 1200);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
					this->model->player->addBullet(9, -1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
					this->model->player->addBullet(10, 7);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
					this->model->player->addBullet(11, 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
					this->model->player->addBullet(12, 5000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
					this->model->player->addBullet(13, 2000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
					this->model->player->addBullet(14, 2000);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					this->model->player->hp = this->model->player->maxhp;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					this->model->shield->addShield(1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
					//this->model->enemySet->spawn(rand() % 2 + 1);
					this->model->enemySet->spawn(5);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
					this->model->gamemode = MODE_MENU_SCREEN;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
					this->model->pause = !this->model->pause;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					if (this->model->player->CURRENT_HOLD_BULLET + 1 != MAX_HOLD_BULLET)
					{
						this->model->player->CURRENT_HOLD_BULLET++;
						this->model->player->holdbuff = HOLD_FOREVER;
					}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					if (this->model->player->CURRENT_HOLD_BULLET != 5)
					{
						this->model->player->CURRENT_HOLD_BULLET--;
						this->model->player->holdbuff = HOLD_FOREVER;
					}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8))
					this->model->droprate->unlock(test++); 

				break;
		}
	}
}