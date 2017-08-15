#pragma once

#include "../Enemy/enemy.hpp"

#include "../defs.h"

class Boss : public Enemy
{

public:

	virtual void initSetup() = 0;

	//information about the boss
	sf::Vector2f primary_shoot;
	sf::Vector2f secondary_shoot;
	sf::Vector2f third_shoot;

	//shoot rate for the boss
	float shoot_count_two;
	float shoot_count_three;

	//y_position target
	float y_target;

	//mode related
	int mode;
	float mode_change;
};