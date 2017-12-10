#pragma once

#include "enemy.hpp"

class Glitchy : public Enemy
{

public:
	Glitchy();										//constructor
	~Glitchy();										//destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};