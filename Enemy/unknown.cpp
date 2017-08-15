#include "unknown.hpp"

Unknown::Unknown() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 30;
	maxhp = 250;
	hp = maxhp;
}

Unknown::~Unknown() {}

void Unknown::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Unknown::update(sf::Time delta_time)
{
	shoot_count += delta_time.asMilliseconds();

	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}