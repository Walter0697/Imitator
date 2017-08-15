#pragma once

#include "enemy.hpp"

class Shotty : public Enemy
{

public:
	Shotty();
	~Shotty();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};