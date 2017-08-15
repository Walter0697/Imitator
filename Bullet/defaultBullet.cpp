#include "defaultBullet.hpp"

DefaultBullet::DefaultBullet() 
{
	//setting of the default bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 650;
	shoot_rate = 1000;
}

DefaultBullet::~DefaultBullet() {}

void DefaultBullet::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void DefaultBullet::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}