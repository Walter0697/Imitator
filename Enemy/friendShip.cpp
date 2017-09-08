#include "friendShip.hpp"

FriendShip::FriendShip() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	speed = 150;
	maxhp = 10;
	hp = maxhp;
}

FriendShip::~FriendShip() {}

void FriendShip::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void FriendShip::update(sf::Time delta_time)
{
}