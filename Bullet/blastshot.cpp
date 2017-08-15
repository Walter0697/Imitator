#include "blastshot.hpp"

BlastShot::BlastShot()
{
	//setting of the blast shot
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 600;
	shoot_rate = 7;
}

BlastShot::~BlastShot() {}

void BlastShot::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void BlastShot::update(sf::Time delta_time)
{
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}