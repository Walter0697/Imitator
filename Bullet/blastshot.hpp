#pragma once

#include "bullet.hpp"

class BlastShot : public Bullet
{

public:
	BlastShot();
	~BlastShot();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};