#include "firework.hpp"

Firework::Firework()
{
	//setting of the default bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 10;
	speed = 500;
	shoot_rate = 0;
}

Firework::~Firework() {}

void Firework::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Firework::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}