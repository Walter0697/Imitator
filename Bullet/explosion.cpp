#include "explosion.hpp"

Explosion::Explosion()
{
	//setting of explosion
	damage = 3;
	lifespan = 1; 
}

Explosion::Explosion(float damage, float lifespan)
{
	this->damage = damage;
	this->lifespan = lifespan;
}

Explosion::~Explosion() {}

void Explosion::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Explosion::update(sf::Time delta_time) 
{
	lifespan -= delta_time.asSeconds();
	if (lifespan <= 0)
	{
		lifespan = 0;
		position = sf::Vector2f(-1800, 0);
		velocity = sf::Vector2f(0, 0);
	}
} 