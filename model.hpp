#pragma once

#include "updateable.hpp"

#include "player.hpp"
#include "bulletSet.hpp"
#include "enemyset.hpp"
#include "toolSet.hpp"
#include "Tools/shield.hpp"
#include "Tools/radShield.hpp"
#include "Mode/story.hpp"
#include "Mode/dropRate.hpp"
#include "Mode/record.hpp"

#include "collision.hpp"

class Model
{

public:
	
	Model();								//constructor
	~Model();								//destructor

	sf::Vector2f screen_tl;					//corners of the screen
	sf::Vector2f screen_br;

	std::vector<Updateable *> updateables;	//all the updateables
	Player* player;							//player

	BulletSet* playerSet;					//player bullets set
	BulletSet* enemyBulletSet;				//enemies bullets set

	EnemySet* enemySet;						//enemies sets
	ToolSet* toolSet;						//tools dropped by enemies in the screen

	Shield* shield;							//two shields of the player
	RadShield* radShield;

	Collision coll;							//collision check
	DropRate* droprate;						//drop rate
	Record* record;							//record of the player

	Story* story;							//story mode

	int gamemode;							//gamemode
	bool pause = false;						//if the game is paused

	float timer;							//timer
	int reward_type = 0;					//reward screen will show up if this is not 0

	int tool_type = 0;						
	float choas_timer;						//related information for choas mode
	float choas_max;
	int boss_chance;

	void updateRewards(sf::Time&);			//all update function for different screen
	void updateStory(sf::Time&);			
	void updateChoas(sf::Time&);
	void updateGame(sf::Time&);
	void update(sf::Time&);
	void modeAdjust(int);					//balancing the boss information according to different mode
	
	void shoot();							//player shooting

	void initAll();							//initialize everything
	
	void specialBulletCheck();				//check for the special bullet
	void checkHit();						//check for the collision
	void enemyShootCount();					//check if enemies should shoot
	void bossShootCount();					//check if the boss should shoot
	void enemyDie(Enemy&, Bullet&, int, int, int);		//drop items and add score if enemy die
	void elementHit(sf::Time);							//if on fire, player or enemy will get damage

	int playerDamage(Bullet&, Hitbox&);					//check if player should get damage
	void bulletDisappear(Bullet&);						//move away the bullet after collision
	
	void enemyDamage(Bullet&, Enemy&, int);				//check if the enemies get damage
	void enemyDamage(Enemy&, int, int);	

	void checkDie(Enemy&, int);				//check if the enemies die

private:
	sf::Vector2f findTarget(sf::Vector2f&);	//find the target for homing
};