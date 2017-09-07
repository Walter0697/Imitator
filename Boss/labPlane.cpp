#include "labPlane.hpp"

LabPlane::LabPlane() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 80;
	maxhp = 15000;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(14, 153);      
	secondary_shoot = sf::Vector2f(213, 283);    
	third_shoot = sf::Vector2f(356, 283);       
	four_shoot = sf::Vector2f(557, 153);         
	five_shoot = sf::Vector2f(285, 352);
}

LabPlane::~LabPlane() {}

void LabPlane::initSetup()
{
	hp = maxhp;
	position.y = -390;
	position.x = SCREEN_WIDTH / 2 - 280;

	shoot_count = 0;   
	shoot_count_two = 400;
	shoot_count_three = 0;   

	y_target = -50;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void LabPlane::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

//not done yet
void LabPlane::update(sf::Time delta_time)
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
		shoot_count_three += delta_time.asMilliseconds();
		this->position.x += this->velocity.x * delta_time.asSeconds();

		if (mode_change < 0)
		{
			mode_change = 5000;
			if (rand() % 10 > chance)
			{
				shoot_count = 0;
				shoot_count_two = 400;
				shoot_count_three = 0;
				chance++;

				if (mode == 2) mode = 3;
				else mode = 2;
			}
			else
				mode = 4;
		}
	}
	//moving to shoot rocket
	else if (mode == 4)
	{
		if (this->position.x > -280)
			this->position.x -= this->speed * 2.1 * delta_time.asSeconds();
		else
		{
			shoot_count_three = 0;
			mode = 5;
		}
	}
	//shooting rocket
	else if (mode == 5)
	{
		if (this->position.x < 520)
		{
			this->position.x += this->speed * 1.8 * delta_time.asSeconds();
			shoot_count_three += delta_time.asMilliseconds();
		}
		else
		{
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 400;
			shoot_count_three = 0;
			mode = 6;
		}
	}
	//back to center
	else if (mode == 6)
	{
		if (this->position.x + 280 > SCREEN_WIDTH / 2)
			this->position.x -= this->speed * 2.1 * delta_time.asSeconds();
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
		if (this->position.y > -390)
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