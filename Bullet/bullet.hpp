#pragma once

#include "../updateable.hpp"

#include <SFML/Graphics.hpp>

class Bullet : public Updateable
{

public:
	//information about the bullet
	float damage;
	float speed;
	float shoot_rate;
};