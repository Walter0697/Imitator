#pragma once

#include "../updateable.hpp"

#include <SFML/Graphics.hpp>

class Enemy : public Updateable
{

public:
	//information about the enemy
	float shoot_count;
	sf::Vector2f velocity;

	float maxhp, hp;
	float speed;

	float onFire = 0;
};