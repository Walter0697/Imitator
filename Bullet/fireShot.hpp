#pragma once

#include "bullet.hpp"

class FireShot : public Bullet
{

public:
	FireShot();
	~FireShot();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};