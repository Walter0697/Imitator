#pragma once

#include "bullet.hpp"

#include "../defs.h"

class LazerBeam : public Bullet
{

public:
	LazerBeam();
	~LazerBeam();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
	void updatePosition(sf::Vector2f&);

	bool isPlayer = true;

	float lifespan;
};