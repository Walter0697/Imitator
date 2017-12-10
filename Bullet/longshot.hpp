#pragma once

#include "bullet.hpp"

class LongShot : public Bullet
{

public:
	LongShot();										//constructor
	~LongShot();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};