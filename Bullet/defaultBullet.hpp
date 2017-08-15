#pragma once

#include "bullet.hpp"

class DefaultBullet : public Bullet
{

public:
	DefaultBullet();
	~DefaultBullet();
	
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);
};