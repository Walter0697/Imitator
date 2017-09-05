#include "friendShip.hpp"

FriendShip::FriendShip() {
	velocity.x = 0;
	velocity.y = 0;

	shoot_count = 0;

	target = sf::Vector2f(-1, -1);

	speed = 50;
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
	if (target.x != -1)
	{
		if (position.x > target.x - 50)
			this->position.x -= this->velocity.x * delta_time.asSeconds();
		else if (position.x < target.x + 50)
			this->position.x += this->velocity.x * delta_time.asSeconds();
		else
			this->position.x = target.x;
		
		if (position.y > target.y - 50)
			this->position.y -= this->velocity.y * delta_time.asSeconds();
		else if (position.y < target.y + 50)
			this->position.y += this->velocity.y * delta_time.asSeconds();
		else
			this->position.y = target.y;
	}

	if (position == target)
		target = sf::Vector2f(-1, -1);
}