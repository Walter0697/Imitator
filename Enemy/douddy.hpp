#pragma once

#include "enemy.hpp"

class Douddy : public Enemy
{

public:
	Douddy();
	~Douddy();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};