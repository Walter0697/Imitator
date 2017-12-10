#pragma once

#include "enemy.hpp"

class Shotty : public Enemy
{

public:
	Shotty();											//constructor
	~Shotty();											//destructor

	void render(sf::RenderWindow&, sf::Sprite&);		//render
	void update(sf::Time);								//update
};