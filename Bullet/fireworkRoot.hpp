#pragma once

#include "bullet.hpp"

class FireworkRoot : public Bullet
{

public:
	FireworkRoot();									//constructor
	~FireworkRoot();								//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};