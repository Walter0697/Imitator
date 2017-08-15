#pragma once

#include "bullet.hpp"

class RandomShot : public Bullet
{

public:
	RandomShot();
	~RandomShot();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};