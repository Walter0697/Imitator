#pragma once

#include "bullet.hpp"

class HomingBullet : public Bullet
{

public:
	HomingBullet();									//constructor
	~HomingBullet();								//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update
	void setTarget(sf::Vector2f&);					//set up target to follow

	float dot;										//math calculate to choose which way the bullet should go
	float angle, turning_speed;
	sf::Vector2f target;

	float target_countdown;							//count down to change the target
};