#pragma once

#include "enemy.hpp"

class DefaultEnemy : public Enemy
{

public:
	DefaultEnemy();									//constructor
	~DefaultEnemy();								//destrcutor

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};