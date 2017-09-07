#include "firethrower.hpp"

FireThrower::FireThrower() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 150;
	maxhp = 8000;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(189, 220);      //fire shot
	secondary_shoot = sf::Vector2f(313, 220);    //fire shot
	third_shoot = sf::Vector2f(30, 220);        //grenade shot
	four_shoot = sf::Vector2f(506, 248);         //grenade shot
	five_shoot = sf::Vector2f(250, 159);          //firework shot
}

FireThrower::~FireThrower() {}

void FireThrower::initSetup()
{
	hp = maxhp;
	position.y = -320;
	position.x = SCREEN_WIDTH / 2 - 280;

	shoot_count = 0;   //fireshot
	shoot_count_two = 200;   //grenade shot
	shoot_count_three = 0;   //firework shot

	countdown = 0;    //for movement

	y_target = -100;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void FireThrower::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void FireThrower::update(sf::Time delta_time)
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
		shoot_count_three += delta_time.asMilliseconds();
		if (countdown <= 0)
		{
			this->position.x += this->velocity.x * delta_time.asSeconds();
			this->position.y += this->velocity.y * delta_time.asSeconds();
		}
		else
		{
			this->position.x += this->velocity.x * 0.15f * delta_time.asSeconds();
			this->position.y += this->velocity.y * 0.6f * delta_time.asSeconds();
			countdown -= delta_time.asMilliseconds();
		}

		if (rand() % 600 < 10 && countdown <= 0)
		{
			countdown = rand() % 100 + 300;
		}

		if (mode_change < 0)
		{
			mode_change = 5000;
			if (rand() % 15 > chance)
			{
				shoot_count = 0;
				shoot_count_two = 200;
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
		if (this->position.x > 200) this->position.x -= this->speed * delta_time.asSeconds();
		else
		{
			velocity.y = 0;
			velocity.x = speed;
			mode_change = 3000;
			mode = 5;
		}
	}
	//shooting firework
	else if (mode == 5)
	{
		shoot_count_three += delta_time.asMilliseconds();
		this->position.x += this->velocity.x * delta_time.asSeconds();

		if (mode_change > 0)
			mode_change -= delta_time.asMilliseconds();
		else
		{
			velocity.x = -speed;
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 200;
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
			this->velocity.x = -speed * 0.2;
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
		if (this->position.y > -320)
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