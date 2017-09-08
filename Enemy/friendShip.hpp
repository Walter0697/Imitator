#pragma once

#include "enemy.hpp"

class FriendShip : public Enemy
{

public:
	FriendShip();
	~FriendShip();

	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};