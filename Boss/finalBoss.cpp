#include "finalBoss.hpp"

FinalBoss::FinalBoss() {
	velocity.x = 0;
	velocity.y = 0;

	speed = 80;
	maxhp = 10000;
	hp = maxhp;

	mode = 0;

	primary_shoot = sf::Vector2f(284, 437);      //lazer beam
	secondary_shoot = sf::Vector2f(147, 349);    
	third_shoot = sf::Vector2f(421, 349);        //two sides
	four_shoot = sf::Vector2f(224, 402);
	five_shoot = sf::Vector2f(347, 402);         //closer two sides
}

FinalBoss::~FinalBoss() {}

void FinalBoss::initSetup()
{
	hp = maxhp;
	position.y = -470;
	position.x = SCREEN_WIDTH / 2 - 280;

	shoot_count = 0;   
	shoot_count_two = 0;  
	shoot_count_three = 0;   

	y_target = -100;

	mode_change = 5000;
	mode = 1;
	chance = 2;
}

void FinalBoss::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

//not done yet
void FinalBoss::update(sf::Time delta_time)
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
	else if (mode >= 2 && mode <= 5)
	{
		mode_change -= delta_time.asMilliseconds();

		shoot_count += delta_time.asMilliseconds();
		shoot_count_two += delta_time.asMilliseconds();
		if (mode == 5)
			this->position.x += this->velocity.x * 2 * delta_time.asSeconds();
		else
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

				mode = rand() % 4 + 2;
			}
			else
				mode = 6;
		}
	}
	//moving to shoot lazerbeam
	else if (mode == 6)
	{
		if (this->position.x > -200)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
			mode = 7;
	}
	//shooting lazerbeam
	else if (mode == 7)
	{
		if (this->position.x < SCREEN_WIDTH - 500)
			this->position.x += this->speed * 2 * delta_time.asSeconds();
		else
		{
			chance = 2;
			shoot_count = 0;
			shoot_count_two = 0;
			shoot_count_three = 0;
			mode = 8;
		}
	}
	//back to center
	else if (mode == 8)
	{
		if (this->position.x + primary_shoot.x > SCREEN_WIDTH / 2)
			this->position.x -= this->speed * 1.2 * delta_time.asSeconds();
		else
		{
			mode = rand() % 4 + 2;
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