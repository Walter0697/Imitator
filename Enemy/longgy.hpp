#pragma once

#include "enemy.hpp"

class Longgy : public Enemy
{

public:
	Longgy();										//constructor
	~Longgy();										//destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};