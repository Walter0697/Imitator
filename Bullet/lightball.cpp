#include "lightball.hpp"

LightBall::LightBall()
{
	//setting of the light ball
	velocity.x = 0;
	velocity.y = 0;
	damage = 5;
	speed = 500;
	shoot_rate = 1500;
}

LightBall::~LightBall() {}

void LightBall::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void LightBall::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}