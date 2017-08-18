#pragma once

#include "updateable.hpp"
#include "renderable.hpp"

#include "hitbox.hpp"

#include "defs.h"

class Player : public Updateable, public Renderable
{

public:
	Player();
	~Player();

	void update(sf::Time);
	void render(sf::RenderWindow&);
	void renderHitbox(sf::RenderWindow&);

	void initialize();

	void addBullet(int, int);
	void addShield(int);

	Hitbox hb;

	float shoot_count[MAX_HOLD_BULLET];
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

	sf::Vector2u size;
	sf::Sprite sprite;
};