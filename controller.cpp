#include "controller.hpp"

Controller::Controller(Model* model, View* view)
{
	this->model = model;
	this->view = view;

	selecting = 1;
}

Controller::~Controller() {}

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
				if (this->selecting == 0)
					this->selecting = MENU_OPTION;
				break;
			case sf::Keyboard::S:
				this->selecting++;
				if (this->selecting == MENU_OPTION + 1)
					this->selecting = 1;
				break;
			}
			this->view->menu->changeSelect(this->selecting);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		switch (this->selecting)
		{
		case 2:
			this->model->initAll();
			this->model->gamemode = MODE_CHAOS_MODE;
			break;
		case 3:
			this->model->initAll();
			this->model->gamemode = MODE_CUSTOM_MODE;
			break;
		case 5:
			this->view->window.close();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (this->model->gamemode == MODE_GAME_OVER)
			this->model->gamemode = MODE_MENU_SCREEN;
	}
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
				this->model->pause = !this->model->pause;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		this->model->gamemode = MODE_MENU_SCREEN;

	//player shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					this->model->shield->addShield(1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
					this->model->enemySet->spawn(rand() % 2 + 1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
					this->model->pause = !this->model->pause;
				break;
		}
	}
}