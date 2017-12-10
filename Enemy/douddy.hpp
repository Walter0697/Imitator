#pragma once

#include "enemy.hpp"

class Douddy : public Enemy
{

public:
	Douddy();										//constructor
	~Douddy();										//destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};