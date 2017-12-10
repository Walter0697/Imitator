#pragma once

#include "bullet.hpp"

class ShotGun : public Bullet
{

public:
	ShotGun();											//constructor
	~ShotGun();											//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);		//render
	void update(sf::Time);								//update

	float lifespan;										//lifespan
};