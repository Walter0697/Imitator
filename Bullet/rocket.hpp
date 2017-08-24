#pragma once

#include "bullet.hpp"

class Rocket : public Bullet
{

public:
	Rocket();
	~Rocket();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};