#pragma once

#include "../updateable.hpp"

#include <SFML/Graphics.hpp>

class Bullet : public Updateable
{

public:
	//information about the bullet
	float damage;						//damage for the bullet
	float speed;						//speed for the bullet
	float shoot_rate;					//fire rate for the bullet
};