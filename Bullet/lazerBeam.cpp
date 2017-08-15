#include "lazerBeam.hpp"

LazerBeam::LazerBeam()
{
	//setting of the lazer beam
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 0;
	shoot_rate = 5000;

	lifespan = 0;
}

LazerBeam::~LazerBeam() {}

void LazerBeam::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position.x - 75, position.y - SCREEN_HEIGHT);
	window.draw(sprite);
}

void LazerBeam::update(sf::Time delta_time)
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

void LazerBeam::updatePosition(sf::Vector2f& position)
{
	if (this->position.y != -3000)
		this->position = position;
}