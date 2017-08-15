#include "longshot.hpp"

LongShot::LongShot() 
{
	//setting of the long shot
	velocity.x = 0;
	velocity.y = 0;
	damage = 60;
	speed = 400;
	shoot_rate = 2000;
}

LongShot::~LongShot() {}

void LongShot::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void LongShot::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}