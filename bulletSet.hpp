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
	//this class is for storing all the bullets within the main screen
	BulletSet(int);							//construtor
											//different hitbox between enemies' and player's bullet so there is an int input for the constructor
											//deciding it is enemy or player constructor
	~BulletSet();							//destructor

	void render(sf::RenderWindow&);			//rendering all the bullets
	void renderHitBox(sf::RenderWindow&);	//rendering all the hitboxes of those bullets
	void update(sf::Time);					//updating all bullets

	void shoot(int, sf::Vector2f, int);		//shooting with direction
	void shoot(int, sf::Vector2f);			//shooting without direction (for boss bullet)

	void initBullet();						//initialize all the bullets
	bool checkOutOfBound(Bullet&);			//check if the bullets are out of bound so it is avaliable to use
	int avaliableBullet(int);				//find an avaliable bullets to shoot

	int isPlayer;							//check if the bullet set belong to the player

	//set up all arrays for the bullets
	//doing it in this way so that we can limit the amount of bullet that show up in the screen
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
	
	//storing all the hitbox of the bullets
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

	//storing all the sprite of the bullets
	//in this way we don't need to store duplicate sprite
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