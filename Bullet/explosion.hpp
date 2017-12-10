#pragma once

#include "bullet.hpp"

class Explosion : public Bullet
{

public:
	Explosion();									//constructor
	Explosion(float, float);
	~Explosion();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update

	float lifespan;									//lifespan of the explosion
};