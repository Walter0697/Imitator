#include "modifier.hpp"

Modifier::Modifier() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 85;
	maxhp = 5000;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(145, 100);      //long shot
	secondary_shoot = sf::Vector2f(430, 100);    //long shot
	third_shoot = sf::Vector2f(216, 321);        //shot gun
	four_shoot = sf::Vector2f(356, 321);         //shot gun
	five_shoot = sf::Vector2f(287, 54);          //blast shot
}

Modifier::~Modifier() {}

void Modifier::initSetup()
{
	hp = maxhp;
	position.y = -373;
	position.x = SCREEN_WIDTH / 2 - 280;

	shoot_count = 0;   //long shot
	shoot_count_two = 0;   //shot gun
	shoot_count_three = 0;   //blast shot

	y_target = -100;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void Modifier::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Modifier::update(sf::Time delta_time)
{
	//entering the screen
	if (mode == 1)
	{
		if (this->position.y < y_target)
			this->position.y += this->speed * 1.2 * delta_time.asSeconds();
		else
		{
			this->velocity.x = -speed;
			mode = 2;
		}
	}
	//shooting normally
	else if (mode == 2 || mode == 3)
	{
		mode_change -= delta_time.asMilliseconds();

		shoot_count += delta_time.asMilliseconds();
		shoot_count_two += delta_time.asMilliseconds();
		this->position.x += this->velocity.x * delta_time.asSeconds();
		this->position.y += this->velocity.y * delta_time.asSeconds();

		if (mode_change < 0)
		{
			mode_change = 5000;
			if (rand() % 15 > chance)
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
	//moving to shoot blast
	else if (mode == 4)
	{
		if (this->position.y > y_target)
			this->position.y -= this->speed * 1.2 * delta_time.asSeconds();
		else
		{
			velocity.y = 0;
			velocity.x = speed;
			mode_change = 5000;
			mode = 5;
		}
	}
	//shooting blast
	else if (mode == 5)
	{
		shoot_count_three += delta_time.asMilliseconds();
		this->position.x += this->velocity.x * delta_time.asSeconds();

		if (mode_change > 0)
			mode_change -= delta_time.asMilliseconds();
		else
		{
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 0;
			shoot_count_three = 0;
			mode_change = 5000;
			mode = 6;
		}
	}
	//back to center
	else if (mode == 6)
	{
		if (this->position.x + five_shoot.x > SCREEN_WIDTH / 2)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
		{
			this->velocity.x = -speed;
			this->velocity.y = 0;
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