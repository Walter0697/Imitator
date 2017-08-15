#pragma once

#include "enemy.hpp"

class Longgy : public Enemy
{

public:
	Longgy();
	~Longgy();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};