#pragma once

#include "bullet.hpp"

class FireShot : public Bullet
{

public:
	FireShot();												//constructor
	~FireShot();											//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);			//render
	void update(sf::Time);									//update
};