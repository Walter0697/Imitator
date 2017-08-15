#pragma once

#include "enemy.hpp"

class Thug : public Enemy
{

public:
	Thug();
	~Thug();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};