#pragma once

#include "bullet.hpp"

class RandomShot : public Bullet
{

public:
	RandomShot();									//constructor
	~RandomShot();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};