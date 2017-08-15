#include "tool.hpp"

Tool::Tool() {}

Tool::~Tool() {}

void Tool::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Tool::update(sf::Time delta_time)
{
	this->position.y += this->velocity.y * delta_time.asSeconds();
	this->position.x += this->velocity.x * delta_time.asSeconds();
}