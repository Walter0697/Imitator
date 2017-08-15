#pragma once

#include "bullet.hpp"

class HomingBullet : public Bullet
{

public:
	HomingBullet();
	~HomingBullet();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
	void setTarget(sf::Vector2f&);

	float dot;
	float angle, turning_speed;
	sf::Vector2f target;

	float target_countdown;
};