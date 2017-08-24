#pragma once

#include "updateable.hpp"
#include "renderable.hpp"

#include "Bullet/defaultBullet.hpp"
#include "Bullet/two_way.hpp"
#include "Bullet/longshot.hpp"
#include "Bullet/shotgun.hpp"
#include "Bullet/lightball.hpp"
#include "Bullet/randomshot.hpp"
#include "Bullet/grenadeLauncher.hpp"
#include "Bullet/explosion.hpp"
#include "Bullet/fireShot.hpp"
#include "Bullet/lazer.hpp"
#include "Bullet/blastshot.hpp"
#include "Bullet/homingbullet.hpp"
#include "Bullet/lazerBeam.hpp"
#include "Bullet/fireworkRoot.hpp"
#include "Bullet/firework.hpp"
#include "Bullet/rocket.hpp"

#include "hitbox.hpp"

#include <SFML/Graphics.hpp>

#include "defs.h"

class BulletSet : public Updateable, public Renderable
{

public:
	BulletSet(int);
	~BulletSet();

	void render(sf::RenderWindow&);
	void renderHitBox(sf::RenderWindow&);
	void update(sf::Time);

	void shoot(int, sf::Vector2f, int);
	void shoot(int, sf::Vector2f);

	void initBullet();
	bool checkOutOfBound(Bullet&);
	int avaliableBullet(int);

	int isPlayer;

	DefaultBullet dbullets[MAX_DBULLET];
	TwoWay twbullets_left[MAX_TWOWAYB];
	TwoWay twbullets_right[MAX_TWOWAYB];
	LongShot longbullets[MAX_LONGSHOT];
	ShotGun shotbullets[MAX_SHOTGUN];
	LightBall lightbullets[MAX_LIGHTBALL];
	RandomShot randombullets[MAX_RANDOMSHOT];
	GrenadeLauncher grenadebullets[MAX_GRENADESHOT];
	Explosion explosions[MAX_EXPLOSION];
	FireShot firebullets[MAX_FIRE_BALL];
	Lazer lazerbullets[MAX_LAZER];
	BlastShot blastbullets[MAX_BLASTSHOT];
	HomingBullet homingbullets[MAX_HOMING];
	LazerBeam lazerbeambullets[MAX_LAZER_BEAM];
	FireworkRoot firerootbullets[MAX_FIRE_ROOT];
	Firework fireworkbullets[MAX_FIRE_WORK];
	Rocket rocketbullets[MAX_ROCKET];
	
	Hitbox hb_dbullet;
	Hitbox hb_twbullet;
	Hitbox hb_longbullet;
	Hitbox hb_shotgun;
	Hitbox hb_lightball;
	Hitbox hb_randombullet;
	Hitbox hb_grenade;
	Hitbox hb_explosion;
	Hitbox hb_fireshot;
	Hitbox hb_lazer;
	Hitbox hb_blastshot;
	Hitbox hb_homingshot;
	Hitbox hb_lazerbeam;
	Hitbox hb_firework;
	Hitbox hb_rocket;

	sf::Sprite sprite_dbullet;
	sf::Sprite sprite_twbullet_left;
	sf::Sprite sprite_twbullet_right;
	sf::Sprite sprite_longbullet;
	sf::Sprite sprite_shotbullet;
	sf::Sprite sprite_lightball;
	sf::Sprite sprite_randombullet;
	sf::Sprite sprite_grenadebullet;
	sf::Sprite sprite_explosion;
	sf::Sprite sprite_fireball;
	sf::Sprite sprite_lazer;
	sf::Sprite sprite_blastshot;
	sf::Sprite sprite_homingshot;
	sf::Sprite sprite_lazerbeam;
	sf::Sprite sprite_fireroot;
	sf::Sprite sprite_firework;
	sf::Sprite sprite_rocket;
};