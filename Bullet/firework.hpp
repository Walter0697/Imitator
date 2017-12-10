#pragma once

#include "bullet.hpp"

class Firework : public Bullet
{

public:
	Firework();										//constructor
	~Firework();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};