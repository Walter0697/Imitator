#pragma once

#include "bullet.hpp"

class GrenadeLauncher : public Bullet
{

public:
	GrenadeLauncher();
	~GrenadeLauncher();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};