#include "rocket.hpp"

Rocket::Rocket()
{
	//setting of the default bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 300;
	speed = 750;
	shoot_rate = 500;
}

Rocket::~Rocket() {}

void Rocket::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Rocket::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}