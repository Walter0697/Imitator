#pragma once

#include "enemy.hpp"

class Lazzy : public Enemy
{

public:
	Lazzy();
	~Lazzy();

	float current_shoot_rate;

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);
};