#pragma once

#include "Enemy\enemy.hpp"
#include "Bullet\bullet.hpp"
#include "player.hpp"

#include "hitbox.hpp"

#include <math.h>

class Collision
{

public:
	Collision();
	~Collision();

	//Rec_tl, Rec_br, Cir_center, Cir_radius
	bool RectangleCircleCollision(sf::Vector2f, sf::Vector2f, sf::Vector2f, float);
	//Rec_tl, Rec_br, Rec2_tl, Rec2_br
	bool RectangleRectangleCollision(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
	//Cir_center, Cir_radius, Cir_center, Cir_radius
	bool CircleCircleCollision(sf::Vector2f, float, sf::Vector2f, float);

	bool ShieldBulletCollision(Player*, float, Bullet&, Hitbox&);
	bool EnemyBulletCollision(Enemy&, Hitbox&, Bullet&, Hitbox&);
	bool PlayerBulletCollision(Player*, Bullet&, Hitbox&);
};