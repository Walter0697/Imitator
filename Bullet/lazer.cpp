#include "lazer.hpp"

Lazer::Lazer()
{
	//setting of the lazer
	velocity.x = 0;
	velocity.y = 0;
	damage = 5;
	speed = 0;
	shoot_rate = -1;

	lifespan = 0;
}

Lazer::~Lazer() {}

void Lazer::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	if (isPlayer)
		sprite.setPosition(position.x - 10, position.y - SCREEN_HEIGHT);
	else
		sprite.setPosition(position.x - 10, position.y);
	window.draw(sprite);
}

void Lazer::update(sf::Time delta_time)
{
	if (lifespan >= 0)
	{
		lifespan -= delta_time.asSeconds();
		if (lifespan <= 0)
		{
			position = sf::Vector2f(0, -3000);
			velocity = sf::Vector2f(0, 0);
		}
	}
}

void Lazer::updatePosition(sf::Vector2f& position)
{
	if (this->position.y != -3000)
		this->position = position;
}