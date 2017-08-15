#pragma once

#include "bullet.hpp"

#include "../defs.h"

class Lazer : public Bullet
{

public:
	Lazer();
	~Lazer();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
	void updatePosition(sf::Vector2f&);

	bool isPlayer = true;

	float lifespan;
};