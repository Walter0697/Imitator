#pragma once

#include "enemy.hpp"

class Gangster : public Enemy
{

public:
	Gangster();										//constructor
	~Gangster();									//destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};