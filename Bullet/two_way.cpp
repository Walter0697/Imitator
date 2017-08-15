#include "two_way.hpp"

TwoWay::TwoWay()
{
	//setting of the two way bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 25;
	speed = 700;
	shoot_rate = 600;
}

TwoWay::~TwoWay() {}

void TwoWay::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void TwoWay::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}