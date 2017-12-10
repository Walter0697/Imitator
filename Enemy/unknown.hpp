#pragma once

#include "enemy.hpp"

class Unknown : public Enemy
{

public:
	Unknown();										//constructor
	~Unknown();										//destructor

	int special_bullet_count = 0;					//since unknown enemy will shoot three bullets in a row, so it needs a little special fire rate
	int current_shoot_rate = 1500;

	void render(sf::RenderWindow&, sf::Sprite&);    //render
	void update(sf::Time);							//update
};