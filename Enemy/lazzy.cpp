#include "lazzy.hpp"

Lazzy::Lazzy() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 20;
	maxhp = 100;
	hp = maxhp;
}

Lazzy::~Lazzy() {}

void Lazzy::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Lazzy::update(sf::Time delta_time)
{
	shoot_count += delta_time.asMilliseconds();

	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}