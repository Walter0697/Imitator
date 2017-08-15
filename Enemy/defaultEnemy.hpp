#pragma once

#include "enemy.hpp"

class DefaultEnemy : public Enemy
{

public:
	DefaultEnemy();
	~DefaultEnemy();

	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};