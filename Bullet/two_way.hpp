#pragma once

#include "bullet.hpp"

class TwoWay : public Bullet
{

public:
	TwoWay();
	~TwoWay();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};