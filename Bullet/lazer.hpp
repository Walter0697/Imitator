#pragma once

#include "bullet.hpp"

#include "../defs.h"

class Lazer : public Bullet
{

public:
	Lazer();											//constructor
	~Lazer();											//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);		//render
	void update(sf::Time);								//update
	void updatePosition(sf::Vector2f&);					//update the position to follow the player/enemy

	bool isPlayer = true;								//see if it belongs to player

	float lifespan;										//lifespan of the bullet
};