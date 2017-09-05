#pragma once

#include "enemy.hpp"

class FriendShip : public Enemy
{

public:
	FriendShip();
	~FriendShip();

	sf::Vector2f target;

	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};