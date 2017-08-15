#include "grenadeLauncher.hpp"

GrenadeLauncher::GrenadeLauncher()
{
	//setting of the default bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 0;
	speed = 650;
	shoot_rate = 1000;
}

GrenadeLauncher::~GrenadeLauncher() {}

void GrenadeLauncher::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void GrenadeLauncher::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}