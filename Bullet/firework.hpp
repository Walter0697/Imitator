#pragma once

#include "bullet.hpp"

class Firework : public Bullet
{

public:
	Firework();
	~Firework();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};