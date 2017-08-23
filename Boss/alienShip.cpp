#include "alienShip.hpp"

AlienShip::AlienShip() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 80;
	maxhp = 8000;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(57, 231);     
	secondary_shoot = sf::Vector2f(82, 257);   
	third_shoot = sf::Vector2f(110, 250);       
	four_shoot = sf::Vector2f(458, 250);         
	five_shoot = sf::Vector2f(485, 257);
	six_shoot = sf::Vector2f(511, 231);
	center_shoot = sf::Vector2f(285, 191);
}

AlienShip::~AlienShip() {}

void AlienShip::initSetup()
{
	hp = maxhp;
	position.y = -325;
	position.x = SCREEN_WIDTH / 2 - 280;
	  
	shoot_count = 0;         //out shoot
	shoot_count_two = 100;     //middle shoot
	shoot_count_three = 200;   //inside shoot

	y_target = -100;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void AlienShip::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void AlienShip::update(sf::Time delta_time)
{
	//entering the screen
	if (mode == 1)
	{
		if (this->position.y < y_target)
			this->position.y += this->speed * 1.2 * delta_time.asSeconds();
		else
			mode = 2;
	}
	//shooting normally
	else if (mode == 2 || mode == 3)
	{
		mode_change -= delta_time.asMilliseconds();

		shoot_count += delta_time.asMilliseconds();
		shoot_count_two += delta_time.asMilliseconds();
		this->position.x += this->velocity.x * delta_time.asSeconds();

		if (mode_change < 0)
		{
			mode_change = 5000;
			if (rand() % 10 > chance)
			{
				shoot_count = 0;
				shoot_count_two = 100;
				shoot_count_three = 200;
				chance++;

				if (mode == 2) mode = 3;
				else mode = 2;
			}
			else
				mode = 4;
		}
	}
	
	else if (mode == 4)
	{
		if (this->position.x > 50)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
			mode = 5;
	}
	//shooting blast
	else if (mode == 5)
	{
		if (this->position.x < SCREEN_WIDTH - 550)
		{
			this->position.x += this->speed * 0.8 * delta_time.asSeconds();
			shoot_count += delta_time.asMilliseconds();
		}
		else
		{
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 0;
			if (rand() % 2 == 1)
				mode = 2;
			else
				mode = 3;
		}
	}
	//ending screen
	else if (mode == 10)
	{
		position = sf::Vector2f(0, 100000);
		velocity = sf::Vector2f(0, 0);
		mode = 0;
	}
}