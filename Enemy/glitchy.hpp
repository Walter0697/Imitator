#pragma once

#include "enemy.hpp"

class Glitchy : public Enemy
{

public:
	Glitchy();
	~Glitchy();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};