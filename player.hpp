#pragma once

#include "updateable.hpp"
#include "renderable.hpp"

#include "hitbox.hpp"

#include "defs.h"

class Player : public Updateable, public Renderable
{

public:
	Player();										//constructor
	~Player();										//destructor

	void update(sf::Time);							//update 
	void render(sf::RenderWindow&);					//render
	void renderHitbox(sf::RenderWindow&);			//render the hitbox of the player

	void initialize();								//initialize

	void addBullet(int, int);						//add the bullet to the player
	void addShield(int);							//add the shield to the player

	Hitbox hb;										//hitbox of the player

	float shoot_count[MAX_HOLD_BULLET];				//shooting information for the player
	int shoot_type[MAX_HOLD_BULLET];
	float shoot_rate[MAX_HOLD_BULLET];
	int shoot_type_s[MAX_HOLD_BULLET];

	//setting of the player
	float speed;
	float maxhp, hp;
	float shield, maxshield;
	int score;
	float onFire = 0;
	float onLuck = 0;

	int CURRENT_HOLD_BULLET = 5;
	float holdbuff = 0;

	//sprite of the player
	sf::Vector2u size;
	sf::Sprite sprite;
	sf::Sprite sprite_onFire;
};