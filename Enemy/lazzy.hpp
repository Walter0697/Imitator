#pragma once

#include "enemy.hpp"

class Lazzy : public Enemy
{

public:
	Lazzy();										//constructor
	~Lazzy();										//destructor

	float current_shoot_rate;						//current fire rate

	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
};