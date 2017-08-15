#pragma once

#include "bullet.hpp"

class Explosion : public Bullet
{

public:
	Explosion();
	Explosion(float, float);
	~Explosion();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	float lifespan;
};