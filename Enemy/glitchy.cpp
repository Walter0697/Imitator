#include "glitchy.hpp"

Glitchy::Glitchy() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 100;
	maxhp = 100;
	hp = maxhp;
}

Glitchy::~Glitchy() {}

void Glitchy::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Glitchy::update(sf::Time delta_time)
{
	shoot_count += delta_time.asMilliseconds();

	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}