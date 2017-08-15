#pragma once

#include "bullet.hpp"

class LongShot : public Bullet
{

public:
	LongShot();
	~LongShot();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};