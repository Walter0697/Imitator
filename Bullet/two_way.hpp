#pragma once

#include "bullet.hpp"

class TwoWay : public Bullet
{

public:
	TwoWay();										//constructor
	~TwoWay();										//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};