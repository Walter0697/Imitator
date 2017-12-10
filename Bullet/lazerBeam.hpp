#pragma once

#include "bullet.hpp"

#include "../defs.h"

class LazerBeam : public Bullet
{

public:
	LazerBeam();										//constructor
	~LazerBeam();										//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);		//render
	void update(sf::Time);								//update
	void updatePosition(sf::Vector2f&);					//update the position to follow the player/enemy

	bool isPlayer = true;								//see if it belongs to player

	float lifespan;										//lifespan of the bullet
};