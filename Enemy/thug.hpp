#pragma once

#include "enemy.hpp"

class Thug : public Enemy
{

public:
	Thug();												//constructor
	~Thug();											//destructor

	void render(sf::RenderWindow&, sf::Sprite&);		//render
	void update(sf::Time);								//update
};