#include "fireShot.hpp"

FireShot::FireShot()
{
	//setting of the fire shot
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 650;
	shoot_rate = 1200;
}

FireShot::~FireShot() {}

void FireShot::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void FireShot::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}