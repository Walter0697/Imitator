#pragma once

#include "enemy.hpp"

class Gangster : public Enemy
{

public:
	Gangster();
	~Gangster();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};