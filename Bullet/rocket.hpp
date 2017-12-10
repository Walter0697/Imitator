#pragma once

#include "bullet.hpp"

class Rocket : public Bullet
{

public:
	Rocket();										//constructor
	~Rocket();										//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};