#include "devPlane.hpp"

DevPlane::DevPlane() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 80;
	maxhp = 2500;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(140, 310);      //default
	secondary_shoot = sf::Vector2f(415, 310);    //default
	third_shoot = sf::Vector2f(280, 360);        //two way
	four_shoot = sf::Vector2f(280, 110);         //lazer bullet
}

DevPlane::~DevPlane() {}

void DevPlane::initSetup()
{
	hp = maxhp;
	position.y = -373;
	position.x = SCREEN_WIDTH / 2 - 280;

	shoot_count = 0;   //default
	shoot_count_two = 0;   //two way
	shoot_count_three = 0;   //lazer bullet

	y_target = -100;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void DevPlane::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void DevPlane::update(sf::Time delta_time)
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
				shoot_count_two = 0;
				shoot_count_three = 0;
				chance++;

				if (mode == 2) mode = 3;
				else mode = 2;
			}
			else
				mode = 4;
		}
	}
	//moving to shoot lazer
	else if (mode == 4)
	{
		if (this->position.x > 50)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
			mode = 5;
	}
	//shooting lazer
	else if (mode == 5)
	{
		if (this->position.x < SCREEN_WIDTH - 550)
			this->position.x += this->speed * 0.8 * delta_time.asSeconds();
		else
		{
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 0;
			mode = 6;
		}
	}
	//back to center
	else if (mode == 6)
	{
		if (this->position.x + four_shoot.x > SCREEN_WIDTH / 2)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
		{
			if (rand() % 2 == 1)
				mode = 2;
			else
				mode = 3;
		}
	}
	//ending screen
	else if (mode == 10)
	{
		if (this->position.y > -373)
			this->position.y -= this->speed * delta_time.asSeconds();
		else 
			mode = 11;
	}
	else if (mode == 11)
	{
		position = sf::Vector2f(0, 100000);
		velocity = sf::Vector2f(0, 0);
		mode = 0;
	}
}