#include "randomshot.hpp"

RandomShot::RandomShot()
{
	//setting of the random shot
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 650;
	shoot_rate = 150;
}

RandomShot::~RandomShot() {}

void RandomShot::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void RandomShot::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}