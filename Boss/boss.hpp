#pragma once

#include "../Enemy/enemy.hpp"

#include "../defs.h"

class Boss : public Enemy
{

public:

	virtual void initSetup() = 0;		//virtual method for boss to have initial setup

	//information about the boss
	sf::Vector2f primary_shoot;			//three different shooting position for the boss
	sf::Vector2f secondary_shoot;
	sf::Vector2f third_shoot;

	//shoot rate for the boss
	float shoot_count_two;				//two different fire rates for the boss
	float shoot_count_three;

	//y_position target
	float y_target;						//the boss will move downward until reaching this position

	//mode related
	int mode;							//current mode for the boss
	float mode_change;					//time remain for the boss to change the mode
};