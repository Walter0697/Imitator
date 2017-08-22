#pragma once

#include "bullet.hpp"

class FireworkRoot : public Bullet
{

public:
	FireworkRoot();
	~FireworkRoot();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};