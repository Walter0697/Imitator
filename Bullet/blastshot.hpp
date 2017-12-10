#pragma once

#include "bullet.hpp"

class BlastShot : public Bullet
{

public:
	BlastShot();									//constructor
	~BlastShot();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};