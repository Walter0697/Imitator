#pragma once

#include "enemy.hpp"

class Unknown : public Enemy
{

public:
	Unknown();
	~Unknown();

	int special_bullet_count = 0;
	int current_shoot_rate = 1500;

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};