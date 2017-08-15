#include "player.hpp"

Player::Player()
{
	//hit box
	this->hb.hitbox_tl = sf::Vector2f(11, 0);
	this->hb.hitbox_br = sf::Vector2f(64, 88);
	this->hb.generateHitboxRec();

	initialize();
}

Player::~Player() {}

//-1 will be lazer shoot
//0-7 will be blast shoot
//8-10 will be homing shoot
void Player::addBullet(int type, int rate)
{
	int empty = -1;
	for (int i = 0; i < MAX_HOLD_BULLET; i++)
	{
		if (shoot_type[i] == 0)
		{
			empty = i;
			break;
		}
	}

	if (empty != -1)
	{
		shoot_type[empty] = type;
		shoot_count[empty] = 0;
		if (rate == -1)
		{
			shoot_rate[empty] = rand() % 600 + 200;
			shoot_type_s[empty] = -1;
		}
		else if (rate == 7)
		{
			shoot_rate[empty] = 4000 * 0.7;
			shoot_type_s[empty] = 7;
		}
		else if (rate == 10)
		{
			shoot_rate[empty] = 1000 * 0.7;
			shoot_type_s[empty] = 10;
		}
		else
		{
			shoot_rate[empty] = rate * 0.7;
			shoot_type_s[empty] = 0;
		}
	}
	else
	{
		for (int i = 0; i < MAX_HOLD_BULLET - 1; i++)
		{
			shoot_type[i] = shoot_type[i + 1];
			shoot_count[i] = shoot_count[i + 1];
			shoot_rate[i] = shoot_rate[i + 1];
			shoot_type_s[i] = shoot_type_s[i + 1];
		}
		shoot_type[MAX_HOLD_BULLET - 1] = type;
		shoot_count[MAX_HOLD_BULLET - 1] = 0;
		if (rate == -1)
		{
			shoot_rate[MAX_HOLD_BULLET - 1] = rand() % 600 + 200;
			shoot_type_s[MAX_HOLD_BULLET - 1] = -1;
		}
		else if (rate == 7)
		{
			shoot_rate[MAX_HOLD_BULLET - 1] = 4000 * 0.7;
			shoot_type_s[MAX_HOLD_BULLET - 1] = 7;
		}
		else if (rate == 10)
		{
			shoot_rate[MAX_HOLD_BULLET - 1] = 1000 * 0.7;
			shoot_type_s[MAX_HOLD_BULLET - 1] = 10;
		}
		else
		{
			shoot_rate[MAX_HOLD_BULLET - 1] = rate * 0.7;
			shoot_type_s[MAX_HOLD_BULLET - 1] = 0;
		}
	}
}

void Player::initialize()
{
	this->position.x = 400;
	this->position.y = 500;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->speed = 500;

	this->maxhp = 500;
	this->hp = this->maxhp;
	this->maxshield = 500;
	this->shield = 0;
	this->onFire = 0;

	this->score = 0;

	//initialize bullets
	for (int i = 0; i < MAX_HOLD_BULLET; i++)
		shoot_count[i] = 0;

	shoot_type[0] = 1;
	for (int i = 1; i < MAX_HOLD_BULLET; i++)
		shoot_type[i] = 0;

	//player will have 30% faster shoot rate than the enemies
	shoot_rate[0] = 1000 * 0.7;
	for (int i = 1; i < MAX_HOLD_BULLET; i++)
		shoot_rate[i] = 0;

	for (int i = 0; i < MAX_HOLD_BULLET; i++)
		shoot_type_s[i] = 0;
}

void Player::addShield(int num)
{
	this->shield += num;
	if (this->shield > this->maxshield) this->shield = this->maxshield;
}

void Player::update(sf::Time deltaTime)
{
	if (this->shield > 0) this->shield -= deltaTime.asSeconds() * 10;
	if (this->shield < 0) this->shield = 0;

	for (int i = 0; i < MAX_HOLD_BULLET; i++)
	{
		if (shoot_count[i] < shoot_rate[i])
			shoot_count[i] += deltaTime.asMilliseconds();
	}

	this->position.x += velocity.x * deltaTime.asSeconds();
	this->position.y += velocity.y * deltaTime.asSeconds();
}

void Player::render(sf::RenderWindow& window)
{
	this->sprite.setPosition(position);
	window.draw(this->sprite);
}

void Player::renderHitbox(sf::RenderWindow& window)
{
	this->hb.rec.setPosition(position.x + hb.hitbox_tl.x, position.y + hb.hitbox_tl.y);
	window.draw(this->hb.rec);
}