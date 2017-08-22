#include "fireworkRoot.hpp"

FireworkRoot::FireworkRoot()
{
	//setting of the default bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 0;
	speed = 300;
	shoot_rate = 2000;
}

FireworkRoot::~FireworkRoot() {}

void FireworkRoot::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void FireworkRoot::update(sf::Time delta_time)
{
	if (velocity.y > 80) velocity.y -= 80 * delta_time.asSeconds();
	else if (velocity.y < -80) velocity.y += 80 * delta_time.asSeconds();
	else velocity.y = 0;

	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}