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
	
	Model();
	~Model();

	sf::Vector2f screen_tl;
	sf::Vector2f screen_br;

	std::vector<Updateable *> updateables;
	Player* player;

	BulletSet* playerSet;
	BulletSet* enemyBulletSet;

	EnemySet* enemySet;
	ToolSet* toolSet;

	Shield* shield;
	RadShield* radShield;

	Collision coll;
	DropRate* droprate;
	Record* record;

	Story* story;

	int gamemode;
	bool pause = false;

	float choas_timer;
	float choas_max;
	int boss_chance;

	void updateStory(sf::Time&);
	void updateChoas(sf::Time&);
	void updateGame(sf::Time&);
	void update(sf::Time&);

	void shoot();

	void initAll();

	void specialBulletCheck();
	void checkHit();
	void enemyShootCount();
	void bossShootCount();
	void enemyDie(Enemy&, Bullet&, int, int, int);
	void elementHit(sf::Time);

	int playerDamage(Bullet&, Hitbox&);
	void bulletDisappear(Bullet&);

	void enemyDamage(Bullet&, Enemy&, int);
	void enemyDamage(Enemy&, int, int);

	void checkDie(Enemy&, int);

private:
	sf::Vector2f findTarget(sf::Vector2f&);
};