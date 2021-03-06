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
	for (int i = MAX_HOLD_BULLET - 1; i > 0; i--)
	{
		shoot_type[i] = shoot_type[i - 1];
		shoot_count[i] = shoot_count[i - 1];
		shoot_rate[i] = shoot_rate[i - 1];
		shoot_type_s[i] = shoot_type_s[i - 1];
	}

	shoot_type[0] = type;
	shoot_count[0] = 0;
	if (rate == -1)
	{
		shoot_rate[0] = rand() % 600 + 200;
		shoot_type_s[0] = -1;
	}
	else if (rate == 7)
	{
		shoot_rate[0] = 4000 * 0.7;
		shoot_type_s[0] = 7;
	}
	else if (rate == 10)
	{
		shoot_rate[0] = 1000 * 0.7;
		shoot_type_s[0] = 10;
	}
	else
	{
		shoot_rate[0] = rate * 0.7;
		shoot_type_s[0] = 0;
	}
}

void Player::initialize()
{
	this->position.x = 400;
	this->position.y = 500;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->speed = 500;

	this->maxhp = 1000;
	this->hp = this->maxhp;
	this->maxshield = 500;
	this->shield = 0;

	this->onFire = 0;
	this->holdbuff = 0;
	this->onLuck = 0;

	this->score = 0;
	CURRENT_HOLD_BULLET = 5;

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

	if (holdbuff != HOLD_FOREVER)
		if (holdbuff > 0)
			holdbuff -= deltaTime.asMilliseconds();
		else
			CURRENT_HOLD_BULLET = 5;

	for (int i = 0; i < CURRENT_HOLD_BULLET; i++)
	{
		if (shoot_count[i] < shoot_rate[i])
			shoot_count[i] += deltaTime.asMilliseconds();
	}

	this->position.x += velocity.x * deltaTime.asSeconds();
	this->position.y += velocity.y * deltaTime.asSeconds();
}

void Player::render(sf::RenderWindow& window)
{
	if (this->onFire > 0)
	{
		this->sprite_onFire.setPosition(position);
		window.draw(this->sprite_onFire);
	}
	else
	{
		this->sprite.setPosition(position);
		window.draw(this->sprite);
	}
}

void Player::renderHitbox(sf::RenderWindow& window)
{
	this->hb.rec.setPosition(position.x + hb.hitbox_tl.x, position.y + hb.hitbox_tl.y);
	window.draw(this->hb.rec);
}