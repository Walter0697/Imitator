#pragma once

#include "enemy.hpp"

class Advanced : public Enemy
{

public:
	Advanced();
	~Advanced();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};