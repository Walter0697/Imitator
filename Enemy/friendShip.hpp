#pragma once

#include "enemy.hpp"

class FriendShip : public Enemy
{

public:
	FriendShip();									//constructor
	~FriendShip();									//destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};