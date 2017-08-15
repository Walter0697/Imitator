#include "thug.hpp"

Thug::Thug() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 25;
	maxhp = 300;
	hp = maxhp;
}

Thug::~Thug() {}

void Thug::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Thug::update(sf::Time delta_time)
{
	shoot_count += delta_time.asMilliseconds();

	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}