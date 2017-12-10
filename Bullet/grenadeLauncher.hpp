#pragma once

#include "bullet.hpp"

class GrenadeLauncher : public Bullet
{

public:
	GrenadeLauncher();								//constructor
	~GrenadeLauncher();								//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};