#pragma once

#include "Enemy\enemy.hpp"
#include "Bullet\bullet.hpp"
#include "player.hpp"

#include "hitbox.hpp"

#include <math.h>

class Collision
{

public:
	//All the collision check will be in this class
	//a facade class to simplifly collision detection
	Collision();							//constructor
	~Collision();							//destructor

	//Rec_tl, Rec_br, Cir_center, Cir_radius
	bool RectangleCircleCollision(sf::Vector2f, sf::Vector2f, sf::Vector2f, float);		//collision detection between rectangle and circle
	//Rec_tl, Rec_br, Rec2_tl, Rec2_br
	bool RectangleRectangleCollision(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);	//collision detection between two rectangles
	//Cir_center, Cir_radius, Cir_center, Cir_radius
	bool CircleCircleCollision(sf::Vector2f, float, sf::Vector2f, float);				//collision detection between two circles

	bool ShieldBulletCollision(Player*, float, Bullet&, Hitbox&);						//collision detection between shield and bullet
	bool EnemyBulletCollision(Enemy&, Hitbox&, Bullet&, Hitbox&);						//collision detection between enemy and bullet
	bool PlayerBulletCollision(Player*, Bullet&, Hitbox&);								//collision detection between player and bullet
};