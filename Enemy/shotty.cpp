#include "shotty.hpp"

Shotty::Shotty() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 15;
	maxhp = 500;
	hp = maxhp;
}

Shotty::~Shotty() {}

void Shotty::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Shotty::update(sf::Time delta_time)
{
	shoot_count += delta_time.asMilliseconds();

	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}