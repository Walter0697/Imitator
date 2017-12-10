#pragma once

#include "bullet.hpp"

class LightBall : public Bullet
{

public:
	LightBall();									//constructor
	~LightBall();									//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};