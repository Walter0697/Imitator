#pragma once

#include "bullet.hpp"

class ShotGun : public Bullet
{

public:
	ShotGun();
	~ShotGun();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	float lifespan;
};