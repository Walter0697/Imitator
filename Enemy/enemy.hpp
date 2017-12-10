#pragma once

#include "../updateable.hpp"

#include <SFML/Graphics.hpp>

class Enemy : public Updateable
{

public:
	//information about the enemy
	float shoot_count;				//fire rate of the enemies
	sf::Vector2f velocity;			//speed of the enemies

	float maxhp, hp;				//health information
	float speed;					//speed

	float onFire = 0;				//check if it is on fire
};