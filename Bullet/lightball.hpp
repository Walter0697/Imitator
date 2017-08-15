#pragma once

#include "bullet.hpp"

class LightBall : public Bullet
{

public:
	LightBall();
	~LightBall();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};