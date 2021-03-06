#include "model.hpp"

Model::Model()
{
	this->screen_tl = sf::Vector2f(0, 0);
	this->screen_br = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->player = new Player();
	this->playerSet = new BulletSet(1);
	this->enemyBulletSet = new BulletSet(2);
	this->enemySet = new EnemySet();
	this->toolSet = new ToolSet();
	this->shield = new Shield(this->player);
	this->radShield = new RadShield(this->player);

	this->droprate = new DropRate();
	this->story = new Story(this->enemySet, this->toolSet, this->droprate, this->player);
	this->record = new Record(this->player, this->story);
	for (int i = 0; i < story->toolUnlock; i++)
		this->droprate->unlock(i + 1);
	if (record->freezeUnlock)
		this->droprate->unlock(7);
	
	this->gamemode = MODE_MENU_SCREEN;
}

Model::~Model() {}

void Model::update(sf::Time& delta_time)
{
	if (delta_time.asSeconds() < 1)
	{
		for (int i = 0; i < this->updateables.size(); i++)
		{
			updateables[i]->update(delta_time);
		}

		//update onLuck
		if (this->player->onLuck > 0)
		{
			this->player->onLuck -= delta_time.asMilliseconds();
			if (this->player->onLuck <= 0)
				this->droprate->multiplier = 1;
		}

		specialBulletCheck();
		enemyShootCount();
		bossShootCount();
	}
}

void Model::specialBulletCheck()
{
	//special type of bullet >> lazer
	for (int i = 0; i < MAX_LAZER; i++)
		if (this->playerSet->lazerbullets[i].lifespan > 0)
			this->playerSet->lazerbullets[i].updatePosition(sf::Vector2f(player->position.x + 36, player->position.y + 26));

	for (int i = 0; i < MAX_LAZER_BEAM; i++)
		if (this->playerSet->lazerbeambullets[i].lifespan > 0)
			this->playerSet->lazerbeambullets[i].updatePosition(sf::Vector2f(player->position.x + 36, player->position.y + 6));

	//spectial type of bullet >> homing
	for (int i = 0; i < MAX_HOMING; i++)
		if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
			this->playerSet->homingbullets[i].setTarget(findTarget(this->playerSet->homingbullets[i].position));
	//homing bullet against player
	for (int i = 0; i < MAX_HOMING; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->homingbullets[i]))
		{
			if (pow(enemyBulletSet->homingbullets[i].position.x - this->player->position.x, 2) + pow(enemyBulletSet->homingbullets[i].position.y - this->player->position.y, 2) < 40000)
				this->enemyBulletSet->homingbullets[i].setTarget(player->position);
			else
				this->enemyBulletSet->homingbullets[i].setTarget(sf::Vector2f(-1, -1));
		}

	//firework bullet
	for (int i = 0; i < MAX_FIRE_ROOT; i++)
	{
		if (!this->playerSet->checkOutOfBound(this->playerSet->firerootbullets[i]))
		{
			if (this->playerSet->firerootbullets[i].velocity.y == 0)
			{
				float angle = rand() % 8;
				while (angle <= 360)
				{
					this->playerSet->fireworkbullets[this->playerSet->avaliableBullet(97)].velocity.y = this->playerSet->fireworkbullets[0].speed * sin(angle * 3.14f / 180.f);
					this->playerSet->fireworkbullets[this->playerSet->avaliableBullet(97)].velocity.x = this->playerSet->fireworkbullets[0].speed * cos(angle * 3.14f / 180.f);
					this->playerSet->fireworkbullets[this->playerSet->avaliableBullet(97)].position = this->playerSet->firerootbullets[i].position;
					angle += rand() % 8 + 1;
				}
				this->playerSet->firerootbullets[i].position = sf::Vector2f(-1800, 0);
			}
		}
	}
	//enemy firework bullet
	for (int i = 0; i < MAX_FIRE_ROOT; i++)
	{
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->firerootbullets[i]))
		{
			if (this->enemyBulletSet->firerootbullets[i].velocity.y == 0)
			{
				float angle = rand() % 10;
				while (angle <= 360)
				{
					this->enemyBulletSet->fireworkbullets[this->enemyBulletSet->avaliableBullet(97)].velocity.y = this->enemyBulletSet->fireworkbullets[0].speed * sin(angle * 3.14f / 180.f);
					this->enemyBulletSet->fireworkbullets[this->enemyBulletSet->avaliableBullet(97)].velocity.x = this->enemyBulletSet->fireworkbullets[0].speed * cos(angle * 3.14f / 180.f);
					this->enemyBulletSet->fireworkbullets[this->enemyBulletSet->avaliableBullet(97)].position = this->enemyBulletSet->firerootbullets[i].position;
					angle += rand() % 20 + 10;
				}
				this->enemyBulletSet->firerootbullets[i].position = sf::Vector2f(-1800, 0);
			}
		}
	}
}

void Model::updateGame(sf::Time& delta_time)
{
	checkHit();
	elementHit(delta_time);

	if (this->player->hp < 0)
	{
		this->player->position = sf::Vector2f(99999, 99999);
		if (this->gamemode != MODE_CUSTOM_MODE)
		{
			switch (this->gamemode)
			{
			case MODE_STORY_MODE:
				record->startPosition = 0;
				record->addRecord(1, "NONAME");
				break;
			case MODE_CHAOS_MODE:
				if (this->story->toolUnlock == 4)
				{
					if (player->score >= IMUMIUM_UNLOCK)
					{
						timer = 2500;
						reward_type = 1;
						story->toolUnlock = 5;
						droprate->unlock(5);
					}
				}
				else if (this->story->toolUnlock == 5)
				{
					if (player->score >= STONE_UNLOCK)
					{
						timer = 2500;
						reward_type = 2;
						story->toolUnlock = 6;
						droprate->unlock(6);
					}
				}
				record->startPosition = 0;
				record->addRecord(2, "NONAME");
				break;
			}
			this->gamemode = MODE_GAME_OVER;
		}
	}
}

void Model::updateRewards(sf::Time& delta_time)
{
	if (timer > 0) timer -= delta_time.asMilliseconds();
}

void Model::updateStory(sf::Time& delta_time)
{
	story->update(delta_time);
}

void Model::updateChoas(sf::Time& delta_time)
{
	choas_timer += delta_time.asMilliseconds();
	if (choas_timer > choas_max)
	{
		choas_timer -= choas_max;
		boss_chance++;
		if (choas_max > 1000)
			choas_max -= 30;

		this->enemySet->spawn(rand() % 11, rand() % SCREEN_WIDTH);
		if (rand() % 450 < boss_chance)
		{
			boss_chance = 0;
			if (this->enemySet->current_boss == 0)
				this->enemySet->spawn(rand() % 6 + 1);
		}
	}
}

void Model::modeAdjust(int current_mode)
{
	switch (current_mode)
	{
	case MODE_CHAOS_MODE:
		this->enemySet->boss_final.maxhp = 20000;
		this->enemySet->boss_labplane.maxhp = 10000;
		break;
	case MODE_STORY_MODE:
		this->enemySet->boss_final.maxhp = 10000;
		this->enemySet->boss_labplane.maxhp = 15000;
		break;
	}
}

void Model::initAll()
{
	player->initialize();
	enemySet->initEnemy();
	playerSet->initBullet();
	enemyBulletSet->initBullet();
	toolSet->initTool();
	story->init();
	record->init();
	droprate->multiplier = 1;
	shield->level = 0;
	radShield->health = 0;
	boss_chance = 0;
	choas_timer = 5000;
	choas_max = 5000;
	pause = false;
	modeAdjust(gamemode);
}

void Model::enemyShootCount()
{
	//enemies shooting count
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		if (!this->enemySet->checkOutOfBound(this->enemySet->denemies[i]))
			if (this->enemySet->denemies[i].shoot_count > this->enemyBulletSet->dbullets[0].shoot_rate)
			{
				this->enemySet->denemies[i].shoot_count -= this->enemyBulletSet->dbullets[0].shoot_rate;
				this->enemyBulletSet->shoot(1, this->enemySet->denemies[i].position, 1);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->douenemies[i]))
			if (this->enemySet->douenemies[i].shoot_count > this->enemyBulletSet->twbullets_left[0].shoot_rate)
			{
				this->enemySet->douenemies[i].shoot_count -= this->enemyBulletSet->twbullets_left[0].shoot_rate;
				this->enemyBulletSet->shoot(2, this->enemySet->douenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->lonenemies[i]))
			if (this->enemySet->lonenemies[i].shoot_count > this->enemyBulletSet->longbullets[0].shoot_rate)
			{
				this->enemySet->lonenemies[i].shoot_count -= this->enemyBulletSet->longbullets[0].shoot_rate;
				this->enemyBulletSet->shoot(3, this->enemySet->lonenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->shotenemies[i]))
			if (this->enemySet->shotenemies[i].shoot_count > this->enemyBulletSet->shotbullets[0].shoot_rate)
			{
				this->enemySet->shotenemies[i].shoot_count -= this->enemyBulletSet->shotbullets[0].shoot_rate;
				this->enemyBulletSet->shoot(4, this->enemySet->shotenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->gangenemies[i]))
			if (this->enemySet->gangenemies[i].shoot_count > this->enemyBulletSet->firebullets[0].shoot_rate)
			{
				this->enemySet->gangenemies[i].shoot_count -= this->enemyBulletSet->firebullets[0].shoot_rate;
				this->enemyBulletSet->shoot(8, this->enemySet->gangenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->thugenemies[i]))
			if (this->enemySet->thugenemies[i].shoot_count > this->enemyBulletSet->grenadebullets[0].shoot_rate)
			{
				this->enemySet->thugenemies[i].shoot_count -= this->enemyBulletSet->grenadebullets[0].shoot_rate;
				this->enemyBulletSet->shoot(7, this->enemySet->thugenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->unknownenemies[i]))
			if (this->enemySet->unknownenemies[i].shoot_count > this->enemySet->unknownenemies[i].current_shoot_rate)
			{
				this->enemySet->unknownenemies[i].shoot_count -= this->enemySet->unknownenemies[i].current_shoot_rate;
				if (this->enemySet->unknownenemies[i].special_bullet_count == 2)
					this->enemySet->unknownenemies[i].current_shoot_rate = 150;
				if (this->enemySet->unknownenemies[i].special_bullet_count > 0)
					this->enemySet->unknownenemies[i].special_bullet_count--;
				else if (this->enemySet->unknownenemies[i].special_bullet_count == 0)
				{
					this->enemySet->unknownenemies[i].special_bullet_count = 2;
					this->enemySet->unknownenemies[i].current_shoot_rate = 3000;
				}
				this->enemyBulletSet->shoot(11, this->enemySet->unknownenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->glitchyenemies[i]))
			if (this->enemySet->glitchyenemies[i].shoot_count > this->enemyBulletSet->randombullets[0].shoot_rate)
			{
				this->enemySet->glitchyenemies[i].shoot_count -= this->enemyBulletSet->randombullets[0].shoot_rate;
				this->enemyBulletSet->shoot(6, this->enemySet->glitchyenemies[i].position, 1);
			}

		if (!this->enemySet->checkOutOfBound(this->enemySet->advancedenemies[i]))
			if (this->enemySet->advancedenemies[i].shoot_count > this->enemyBulletSet->lightbullets[0].shoot_rate)
			{
				this->enemySet->advancedenemies[i].shoot_count -= this->enemyBulletSet->lightbullets[0].shoot_rate;
				this->enemyBulletSet->shoot(5, this->enemySet->advancedenemies[i].position, 1);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->lazzyenemies[i]))
			if (this->enemySet->lazzyenemies[i].shoot_count > this->enemySet->lazzyenemies[i].current_shoot_rate)
			{
				this->enemySet->lazzyenemies[i].shoot_count -= this->enemySet->lazzyenemies[i].current_shoot_rate;
				this->enemySet->lazzyenemies[i].current_shoot_rate = rand() % 600 + 200;
				this->enemyBulletSet->shoot(9, this->enemySet->lazzyenemies[i].position, 1);
			}
	}
}

void Model::bossShootCount()
{
	//devplane
	if (this->enemySet->current_boss == 1)
	{
		if (this->enemySet->boss_devplane.mode == 2)
		{
			if (this->enemySet->boss_devplane.shoot_count > 200)
			{
				this->enemySet->boss_devplane.shoot_count -= 200;
				this->enemyBulletSet->shoot(1, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.primary_shoot);
				this->enemyBulletSet->shoot(1, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.secondary_shoot);
			}
		}
		else if (this->enemySet->boss_devplane.mode == 3)
		{
			if (this->enemySet->boss_devplane.shoot_count > 400)
			{
				this->enemySet->boss_devplane.shoot_count -= 400;
				this->enemyBulletSet->shoot(1, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.primary_shoot);
				this->enemyBulletSet->shoot(1, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.secondary_shoot);
			}
			if (this->enemySet->boss_devplane.shoot_count_two > 150)
			{
				this->enemySet->boss_devplane.shoot_count_two -= 150;
				this->enemyBulletSet->shoot(2, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.third_shoot);
				this->enemyBulletSet->shoot(99, this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.third_shoot);
			}
		}
		else if (this->enemySet->boss_devplane.mode == 5)
		{
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.four_shoot;
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.primary_shoot;
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 3].position = this->enemySet->boss_devplane.position + this->enemySet->boss_devplane.secondary_shoot;
		}
		else if (this->enemySet->boss_devplane.mode == 6)
		{
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 3].position = sf::Vector2f(-3000, 0);
		}
	}
	//modifier
	else if (this->enemySet->current_boss == 2)
	{
		if (this->enemySet->boss_modifier.mode == 2)
		{
			if (this->enemySet->boss_modifier.shoot_count > 600)
			{
				this->enemySet->boss_modifier.shoot_count -= 600;
				this->enemyBulletSet->shoot(3, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.primary_shoot);
				this->enemyBulletSet->shoot(3, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.secondary_shoot);
			}
			if (this->enemySet->boss_modifier.shoot_count_two > 500)
			{
				this->enemySet->boss_modifier.shoot_count_two -= 500;
				this->enemyBulletSet->shoot(4, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.third_shoot);
				this->enemyBulletSet->shoot(4, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.four_shoot);
			}
		}
		else if (this->enemySet->boss_modifier.mode == 3)
		{
			if (this->enemySet->boss_modifier.shoot_count > 300)
			{
				this->enemySet->boss_modifier.shoot_count -= 300;
				this->enemyBulletSet->shoot(1, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.primary_shoot);
				this->enemyBulletSet->shoot(1, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.secondary_shoot);
			}
			if (this->enemySet->boss_modifier.shoot_count_two > 300)
			{
				this->enemySet->boss_modifier.shoot_count_two -= 300;
				this->enemyBulletSet->shoot(2, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.third_shoot);
				this->enemyBulletSet->shoot(99, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.third_shoot);
				this->enemyBulletSet->shoot(2, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.four_shoot);
				this->enemyBulletSet->shoot(99, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.four_shoot);
			}
		}
		else if (this->enemySet->boss_modifier.mode == 5)
		{
			if (this->enemySet->boss_modifier.shoot_count_three > 80)
			{
				this->enemySet->boss_modifier.shoot_count_three -= 80;
				this->enemyBulletSet->shoot(10, this->enemySet->boss_modifier.position + this->enemySet->boss_modifier.five_shoot);
			}
		}
	}
	//firethrower
	else if (this->enemySet->current_boss == 3)
	{
		if (this->enemySet->boss_firethrower.mode == 2)
		{
			if (this->enemySet->boss_firethrower.shoot_count > 700)
			{
				this->enemySet->boss_firethrower.shoot_count -= 700;
				this->enemyBulletSet->shoot(8, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.primary_shoot);
			}
			if (this->enemySet->boss_firethrower.shoot_count_two > 700)
			{
				this->enemySet->boss_firethrower.shoot_count_two -= 700;
				this->enemyBulletSet->shoot(8, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.secondary_shoot);
			}
			if (this->enemySet->boss_firethrower.shoot_count_three > 500)
			{
				this->enemySet->boss_firethrower.shoot_count_three -= 500;
				this->enemyBulletSet->shoot(7, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.third_shoot);
				this->enemyBulletSet->shoot(7, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.four_shoot);
			}
		}
		else if (this->enemySet->boss_firethrower.mode == 3)
		{
			if (this->enemySet->boss_firethrower.shoot_count > 700)
			{
				this->enemySet->boss_firethrower.shoot_count -= 700;
				this->enemyBulletSet->shoot(7, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.primary_shoot);
			}
			if (this->enemySet->boss_firethrower.shoot_count_two > 700)
			{
				this->enemySet->boss_firethrower.shoot_count_two -= 700;
				this->enemyBulletSet->shoot(7, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.secondary_shoot);
			}
			if (this->enemySet->boss_firethrower.shoot_count_three > 500)
			{
				this->enemySet->boss_firethrower.shoot_count_three -= 500;
				this->enemyBulletSet->shoot(8, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.third_shoot);
				this->enemyBulletSet->shoot(8, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.four_shoot);
			}
		}
		else if (this->enemySet->boss_firethrower.mode == 5)
		{
			if (this->enemySet->boss_firethrower.shoot_count_three > 400)
			{
				this->enemySet->boss_firethrower.shoot_count_three -= 400;
				this->enemyBulletSet->shoot(13, this->enemySet->boss_firethrower.position + this->enemySet->boss_firethrower.five_shoot);
			}
		}
	}
	//alienShip
	else if (this->enemySet->current_boss == 4)
	{
		if (this->enemySet->boss_alien.mode == 2)
		{
			if (this->enemySet->boss_alien.shoot_count > 1000)
			{
				this->enemySet->boss_alien.shoot_count -= 1000;
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.primary_shoot);
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.six_shoot);
			}
			if (this->enemySet->boss_alien.shoot_count_two > 1000)
			{
				this->enemySet->boss_alien.shoot_count_two -= 1000;
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.secondary_shoot);
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.five_shoot);
			}
			if (this->enemySet->boss_alien.shoot_count_three > 1000)
			{
				this->enemySet->boss_alien.shoot_count_three -= 1000;
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.third_shoot);
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.four_shoot);
			}
		}
		else if (this->enemySet->boss_alien.mode == 3)
		{
			if (this->enemySet->boss_alien.shoot_count > 800)
			{
				this->enemySet->boss_alien.shoot_count -= 800;
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.primary_shoot);
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.six_shoot);
			}
			if (this->enemySet->boss_alien.shoot_count_two > 1600)
			{
				this->enemySet->boss_alien.shoot_count_two -= 1600;
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.third_shoot);
				this->enemyBulletSet->shoot(11, this->enemySet->boss_alien.position + this->enemySet->boss_alien.four_shoot);
			}
		}
		else if (this->enemySet->boss_alien.mode == 5)
		{
			if (this->enemySet->boss_alien.shoot_count > 500)
			{
				this->enemySet->boss_alien.shoot_count -= 500;
				this->enemyBulletSet->shoot(10, this->enemySet->boss_alien.position + this->enemySet->boss_alien.center_shoot);
			}
		}
	}
	//labplane
	else if (this->enemySet->current_boss == 5)
	{
		if (this->enemySet->boss_labplane.mode == 2 || this->enemySet->boss_labplane.mode == 3)
		{
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.primary_shoot;
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.four_shoot;
			if (this->enemySet->boss_labplane.mode == 2)
			{
				if (this->enemySet->boss_labplane.shoot_count > 800)
				{
					this->enemySet->boss_labplane.shoot_count -= 800;
					this->enemyBulletSet->shoot(5, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.secondary_shoot);
				}
				if (this->enemySet->boss_labplane.shoot_count_two > 800)
				{
					this->enemySet->boss_labplane.shoot_count_two -= 800;
					this->enemyBulletSet->shoot(5, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.third_shoot);
				}
				if (this->enemySet->boss_labplane.shoot_count_three > 2800)
				{
					this->enemySet->boss_labplane.shoot_count_three -= 2800;
					for (int i = 0; i < 3; i++)
						this->enemySet->spawn(9, ((i + 1.f) / 4.f) * SCREEN_WIDTH);
				}
			}
			else
			{
				if (this->enemySet->boss_labplane.shoot_count > 1000)
				{
					this->enemySet->boss_labplane.shoot_count -= 1000;
					this->enemyBulletSet->shoot(5, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.secondary_shoot);
					this->enemyBulletSet->shoot(5, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.third_shoot);
				}
				if (this->enemySet->boss_labplane.shoot_count_two > 100)
				{
					this->enemySet->boss_labplane.shoot_count_two -= 100;
					this->enemyBulletSet->shoot(6, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.five_shoot);
					this->enemyBulletSet->shoot(6, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.five_shoot);
				}
				if (this->enemySet->boss_labplane.shoot_count_three > 2800)
				{
					this->enemySet->boss_labplane.shoot_count_three -= 2800;
					this->enemySet->spawn(8, rand() % SCREEN_WIDTH);
				}
			}
		}
		else if (this->enemySet->boss_labplane.mode == 4)
		{
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = sf::Vector2f(-3000, 0);
		}
		else if (this->enemySet->boss_labplane.mode == 5)
		{
			if (this->enemySet->boss_labplane.shoot_count_three > 300)
			{
				this->enemySet->boss_labplane.shoot_count_three -= 300;
				this->enemyBulletSet->shoot(14, this->enemySet->boss_labplane.position + this->enemySet->boss_labplane.five_shoot);
			}
		}
	}
	//final boss
	else if (this->enemySet->current_boss == 6)
	{
		if (this->enemySet->boss_final.mode == 2)
		{
			if (this->enemySet->boss_final.shoot_count > 400)
			{
				this->enemySet->boss_final.shoot_count -= 400;
				this->enemyBulletSet->shoot(1, this->enemySet->boss_final.position + this->enemySet->boss_final.secondary_shoot);
				this->enemyBulletSet->shoot(1, this->enemySet->boss_final.position + this->enemySet->boss_final.third_shoot);
			}
			if (this->enemySet->boss_final.shoot_count_two > 300)
			{
				this->enemySet->boss_final.shoot_count_two -= 300;
				this->enemyBulletSet->shoot(2, this->enemySet->boss_final.position + this->enemySet->boss_final.four_shoot);
				this->enemyBulletSet->shoot(99, this->enemySet->boss_final.position + this->enemySet->boss_final.four_shoot);
				this->enemyBulletSet->shoot(2, this->enemySet->boss_final.position + this->enemySet->boss_final.five_shoot);
				this->enemyBulletSet->shoot(99, this->enemySet->boss_final.position + this->enemySet->boss_final.five_shoot);
			}
		}
		else if (this->enemySet->boss_final.mode == 3)
		{
			if (this->enemySet->boss_final.shoot_count > 600)
			{
				this->enemySet->boss_final.shoot_count -= 600;
				this->enemyBulletSet->shoot(7, this->enemySet->boss_final.position + this->enemySet->boss_final.secondary_shoot);
				this->enemyBulletSet->shoot(7, this->enemySet->boss_final.position + this->enemySet->boss_final.third_shoot);
			}
			if (this->enemySet->boss_final.shoot_count_two > 200)
			{
				this->enemySet->boss_final.shoot_count_two -= 200;
				this->enemyBulletSet->shoot(6, this->enemySet->boss_final.position + this->enemySet->boss_final.four_shoot);
				this->enemyBulletSet->shoot(6, this->enemySet->boss_final.position + this->enemySet->boss_final.five_shoot);
			}
		}
		else if (this->enemySet->boss_final.mode == 4)
		{
			if (this->enemySet->boss_final.shoot_count > 700)
			{
				this->enemySet->boss_final.shoot_count -= 700;
				this->enemyBulletSet->shoot(8, this->enemySet->boss_final.position + this->enemySet->boss_final.secondary_shoot);
				this->enemyBulletSet->shoot(8, this->enemySet->boss_final.position + this->enemySet->boss_final.third_shoot);
			}
			if (this->enemySet->boss_final.shoot_count_two > 2000)
			{
				this->enemySet->boss_final.shoot_count_two -= 2000;
				this->enemyBulletSet->shoot(13, this->enemySet->boss_final.position + this->enemySet->boss_final.four_shoot);
				this->enemyBulletSet->shoot(13, this->enemySet->boss_final.position + this->enemySet->boss_final.five_shoot);
			}
		}
		else if (this->enemySet->boss_final.mode == 5)
		{
			if (this->enemySet->boss_final.shoot_count > 800)
			{
				this->enemySet->boss_final.shoot_count -= 800;
				this->enemyBulletSet->shoot(10, this->enemySet->boss_final.position + this->enemySet->boss_final.four_shoot);
				this->enemyBulletSet->shoot(10, this->enemySet->boss_final.position + this->enemySet->boss_final.five_shoot);
			}
		}
		else if (this->enemySet->boss_final.mode == 7)
		{
			this->enemyBulletSet->lazerbeambullets[MAX_LAZER_BEAM - 1].position = this->enemySet->boss_final.position + this->enemySet->boss_final.primary_shoot;
		}
		else if (this->enemySet->boss_final.mode == 8)
		{
			this->enemyBulletSet->lazerbeambullets[MAX_LAZER_BEAM - 1].position = sf::Vector2f(-3000, 0);
		}
	}
}

void Model::shoot()
{
	for (int i = 0; i < player->CURRENT_HOLD_BULLET; i++)
	{
		if (this->player->shoot_type[i] != 0)
		{
			if (this->player->shoot_count[i] >= this->player->shoot_rate[i])
			{
				this->player->shoot_count[i] -= this->player->shoot_rate[i];
				this->playerSet->shoot(this->player->shoot_type[i], this->player->position, -1);

				if (this->player->shoot_type_s[i] == -1)
					this->player->shoot_rate[i] = rand() % 600 + 200;
				else if (this->player->shoot_type_s[i] > 1 && this->player->shoot_type_s[i] <= 7)
				{
					this->player->shoot_rate[i] = 80;
					this->player->shoot_type_s[i]--;
				}
				else if (this->player->shoot_type_s[i] == 1)
				{
					this->player->shoot_rate[i] = 4000 * 0.7;
					this->player->shoot_type_s[i] = 7;
				}
				else if (this->player->shoot_type_s[i] > 8 && this->player->shoot_type_s[i] <= 10)
				{
					this->player->shoot_rate[i] = 100;
					this->player->shoot_type_s[i]--;
				}
				else if (this->player->shoot_type_s[i] == 8)
				{
					this->player->shoot_rate[i] = 1000 * 0.7;
					this->player->shoot_type_s[i] = 10;
				}
			}
		}
	}
}

void Model::elementHit(sf::Time delta_time)
{
	//enemies elemenet hit
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		if (!this->enemySet->checkOutOfBound(this->enemySet->denemies[i]))
			if (this->enemySet->denemies[i].onFire > 0)
			{
				this->enemySet->denemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->denemies[i], FIRE_HIT, 1);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->douenemies[i]))
			if (this->enemySet->douenemies[i].onFire > 0)
			{
				this->enemySet->douenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->douenemies[i], FIRE_HIT, 2);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->lonenemies[i]))
			if (this->enemySet->lonenemies[i].onFire > 0)
			{
				this->enemySet->lonenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->lonenemies[i], FIRE_HIT, 3);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->shotenemies[i]))
			if (this->enemySet->shotenemies[i].onFire > 0)
			{
				this->enemySet->shotenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->shotenemies[i], FIRE_HIT, 4);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->gangenemies[i]))
			if (this->enemySet->gangenemies[i].onFire > 0)
			{
				this->enemySet->gangenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->gangenemies[i], FIRE_HIT, 5);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->thugenemies[i]))
			if (this->enemySet->thugenemies[i].onFire > 0)
			{
				this->enemySet->thugenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->thugenemies[i], FIRE_HIT, 6);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->unknownenemies[i]))
			if (this->enemySet->unknownenemies[i].onFire > 0)
			{
				this->enemySet->unknownenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->unknownenemies[i], FIRE_HIT, 7);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->glitchyenemies[i]))
			if (this->enemySet->glitchyenemies[i].onFire > 0)
			{
				this->enemySet->glitchyenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->glitchyenemies[i], FIRE_HIT, 8);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->advancedenemies[i]))
			if (this->enemySet->advancedenemies[i].onFire > 0)
			{
				this->enemySet->advancedenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->advancedenemies[i], FIRE_HIT, 9);
			}
		if (!this->enemySet->checkOutOfBound(this->enemySet->lazzyenemies[i]))
			if (this->enemySet->lazzyenemies[i].onFire > 0)
			{
				this->enemySet->lazzyenemies[i].onFire -= delta_time.asSeconds();
				enemyDamage(this->enemySet->lazzyenemies[i], FIRE_HIT, 10);
			}
	}

	//boss element hit
	if (!this->enemySet->checkOutOfBound(this->enemySet->boss_devplane))
		if (this->enemySet->boss_devplane.onFire > 0)
		{
			this->enemySet->boss_devplane.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_devplane, FIRE_HIT, 91);
		}
	if (!this->enemySet->checkOutOfBound(this->enemySet->boss_modifier))
		if (this->enemySet->boss_modifier.onFire > 0)
		{
			this->enemySet->boss_modifier.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_modifier, FIRE_HIT, 92);
		}
	if (!this->enemySet->checkOutOfBound(this->enemySet->boss_firethrower))
		if (this->enemySet->boss_firethrower.onFire > 0)
		{
			this->enemySet->boss_firethrower.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_firethrower, FIRE_HIT, 93);
		}
	if (this->enemySet->checkOutOfBound(this->enemySet->boss_alien))
		if (this->enemySet->boss_alien.onFire > 0)
		{
			this->enemySet->boss_alien.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_alien, FIRE_HIT, 94);
		}
	if (this->enemySet->checkOutOfBound(this->enemySet->boss_labplane))
		if (this->enemySet->boss_labplane.onFire > 0)
		{
			this->enemySet->boss_labplane.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_labplane, FIRE_HIT, 95);
		}
	if (this->enemySet->checkOutOfBound(this->enemySet->boss_final))
		if (this->enemySet->boss_final.onFire > 0)
		{
			this->enemySet->boss_final.onFire -= delta_time.asSeconds();
			enemyDamage(this->enemySet->boss_final, FIRE_HIT, 96);
		}

	//player element hit
	if (this->player->onFire > 0)
	{
		this->player->onFire -= delta_time.asSeconds();
		this->player->hp -= FIRE_HIT;
	}
}

void Model::checkHit()
{
	///////////////////////////////////////////////////////
	////////////////////BULLET VS ENEMY////////////////////
	///////////////////////////////////////////////////////
	
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		//default bullet vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_DBULLET; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->dbullets[j], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//two way vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_TWOWAYB; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->twbullets_left[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[j], this->enemySet->friendShips[i], 11);
			}

			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->douenemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->denemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->twbullets_right[j], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[j], this->enemySet->friendShips[i], 11);
			}
		}

		//long shot vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_LONGSHOT; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->longbullets[j], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//shot gun vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_SHOTGUN; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->shotbullets[j], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//light ball vs default + douddy + longgy  + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_LIGHTBALL; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->denemies[i], this->playerSet->lightbullets[j].damage, 1);
				if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->douenemies[i], this->playerSet->lightbullets[j].damage, 2);
				if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->lonenemies[i], this->playerSet->lightbullets[j].damage, 3);
				if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->shotenemies[i], this->playerSet->lightbullets[j].damage, 4);
				if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->gangenemies[i], this->playerSet->lightbullets[j].damage, 5);
				if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->thugenemies[i], this->playerSet->lightbullets[j].damage, 6);
				if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->unknownenemies[i], this->playerSet->lightbullets[j].damage, 7);
				if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->glitchyenemies[i], this->playerSet->lightbullets[j].damage, 8);
				if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->advancedenemies[i], this->playerSet->lightbullets[j].damage, 9);
				if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->lazzyenemies[i], this->playerSet->lightbullets[j].damage, 10);
				if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->lightbullets[j], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->friendShips[i], this->playerSet->lightbullets[j].damage, 11);
			}
		}

		//randombullet vs default + douddy  + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_RANDOMSHOT; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->gangenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->randombullets[j], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//grenade launcher vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_GRENADESHOT; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade) ||
					coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->grenadebullets[j], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[j].position;
					this->playerSet->grenadebullets[j].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[j].velocity = sf::Vector2f(0, 0);
				}
			}
		}

		//explosion vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_EXPLOSION; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->denemies[i], this->playerSet->explosions[j].damage, 1);
				if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->douenemies[i], this->playerSet->explosions[j].damage, 2);
				if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->lonenemies[i], this->playerSet->explosions[j].damage, 3);
				if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->shotenemies[i], this->playerSet->explosions[j].damage, 4);
				if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->gangenemies[i], this->playerSet->explosions[j].damage, 5);
				if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->thugenemies[i], this->playerSet->explosions[j].damage, 6);
				if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->unknownenemies[i], this->playerSet->explosions[j].damage, 7);
				if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->glitchyenemies[i], this->playerSet->explosions[j].damage, 8);
				if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->advancedenemies[i], this->playerSet->explosions[j].damage, 9);
				if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->lazzyenemies[i], this->playerSet->explosions[j].damage, 10);
				if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->explosions[j], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->friendShips[i], this->playerSet->explosions[j].damage, 11);
			}
		}

		//fireball vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_FIRE_BALL; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->denemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->denemies[i], 1);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->douenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->douenemies[i], 2);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->lonenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->lonenemies[i], 3);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->shotenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->shotenemies[i], 4);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->gangenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->gangenemies[i], 5);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->thugenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->thugenemies[i], 6);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->unknownenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->unknownenemies[i], 7);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->glitchyenemies[i].onFire - rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->glitchyenemies[i], 8);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->advancedenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->advancedenemies[i], 9);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->lazzyenemies[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->lazzyenemies[i], 10);
				}
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->firebullets[j], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->friendShips[i].onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[j], this->enemySet->friendShips[i], 11);
				}
			}
		}

		//lazer vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_LAZER; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->denemies[i], this->playerSet->lazerbullets[j].damage, 1);
				if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->douenemies[i], this->playerSet->lazerbullets[j].damage, 2);
				if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->lonenemies[i], this->playerSet->lazerbullets[j].damage, 3);
				if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->shotenemies[i], this->playerSet->lazerbullets[j].damage, 4);
				if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->gangenemies[i], this->playerSet->lazerbullets[j].damage, 5);
				if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->thugenemies[i], this->playerSet->lazerbullets[j].damage, 6);
				if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->unknownenemies[i], this->playerSet->lazerbullets[j].damage, 7);
				if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->glitchyenemies[i], this->playerSet->lazerbullets[j].damage, 8);
				if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->advancedenemies[i], this->playerSet->lazerbullets[j].damage, 9);
				if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->lazzyenemies[i], this->playerSet->lazerbullets[j].damage, 10);
				if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->lazerbullets[j], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->friendShips[i], this->playerSet->lazerbullets[j].damage, 11);
			}
		}

		//blast vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_BLASTSHOT; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->blastbullets[j], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//homing vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_HOMING; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->homingbullets[j], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//lazer beam vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_LAZER_BEAM; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->denemies[i], this->playerSet->lazerbeambullets[j].damage, 1);
				if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->douenemies[i], this->playerSet->lazerbeambullets[j].damage, 2);
				if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->lonenemies[i], this->playerSet->lazerbeambullets[j].damage, 3);
				if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->shotenemies[i], this->playerSet->lazerbeambullets[j].damage, 4);
				if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->gangenemies[i], this->playerSet->lazerbeambullets[j].damage, 5);
				if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->thugenemies[i], this->playerSet->lazerbeambullets[j].damage, 6);
				if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->unknownenemies[i], this->playerSet->lazerbeambullets[j].damage, 7);
				if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->glitchyenemies[i], this->playerSet->lazerbeambullets[j].damage, 8);
				if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->advancedenemies[i], this->playerSet->lazerbeambullets[j].damage, 9);
				if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->lazzyenemies[i], this->playerSet->lazerbeambullets[j].damage, 10);
				if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->lazerbeambullets[j], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->friendShips[i], this->playerSet->lazerbeambullets[j].damage, 11);
			}
		}

		//firework vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_FIRE_WORK; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->denemies[i], 1);
				else if (coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->douenemies[i], 2);
				else if (coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->lonenemies[i], 3);
				else if (coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->shotenemies[i], 4);
				else if (coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->gangenemies[i], 5);
				else if (coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->thugenemies[i], 6);
				else if (coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->unknownenemies[i], 7);
				else if (coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->glitchyenemies[i], 8);
				else if (coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->advancedenemies[i], 9);
				else if (coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->lazzyenemies[i], 10);
				else if (coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->fireworkbullets[j], this->playerSet->hb_firework))
					enemyDamage(this->playerSet->fireworkbullets[j], this->enemySet->friendShips[i], 11);
			}
		}

		//rocket vs default + douddy + longgy + shotty + gangster + thug + unknown + glitchy + advanced + lazzy enemy
		for (int j = 0; j < MAX_ROCKET; j++)
		{
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[j]))
			{
				if (coll.EnemyBulletCollision(this->enemySet->denemies[i], this->enemySet->hb_denemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->douenemies[i], this->enemySet->hb_douenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->lonenemies[i], this->enemySet->hb_longenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->shotenemies[i], this->enemySet->hb_shotenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->gangenemies[i], this->enemySet->hb_gangenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->thugenemies[i], this->enemySet->hb_thugenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->unknownenemies[i], this->enemySet->hb_unknownenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->glitchyenemies[i], this->enemySet->hb_glitchyenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->advancedenemies[i], this->enemySet->hb_advancedenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->lazzyenemies[i], this->enemySet->hb_lazzyenemy, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket) ||
					coll.EnemyBulletCollision(this->enemySet->friendShips[i], this->enemySet->hb_friend, this->playerSet->rocketbullets[j], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[j].position;
					this->playerSet->rocketbullets[j].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[j].velocity = sf::Vector2f(0, 0);
				}
			}
		}
	}
	
	///////////////////////////////////////////////////////
	/////////////////////BULLET VS BOSS////////////////////
	///////////////////////////////////////////////////////
	//bullet vs devplane
	if (enemySet->boss_devplane.mode >= 2 && enemySet->boss_devplane.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_devplane, this->playerSet->lightbullets[i].damage, 91);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_devplane, this->playerSet->explosions[i].damage, 91);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_devplane.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_devplane, 91);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_devplane, this->playerSet->lazerbullets[i].damage, 91);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_devplane, 91);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_devplane, this->playerSet->lazerbeambullets[i].damage, 91);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_devplane, this->playerSet->fireworkbullets[i].damage, 91);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_devplane, this->enemySet->hb_boss_devplane, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}
	//bullet vs modifier
	else if (enemySet->boss_modifier.mode >= 2 && enemySet->boss_modifier.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_modifier, this->playerSet->lightbullets[i].damage, 92);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_modifier, this->playerSet->explosions[i].damage, 92);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_modifier.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_modifier, 92);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_modifier, this->playerSet->lazerbullets[i].damage, 92);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_modifier, 92);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_modifier, this->playerSet->lazerbeambullets[i].damage, 92);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_modifier, this->playerSet->fireworkbullets[i].damage, 92);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_modifier, this->enemySet->hb_boss_modifier, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}
	//bullet vs firethrower
	else if (enemySet->boss_firethrower.mode >= 2 && enemySet->boss_firethrower.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_firethrower, this->playerSet->lightbullets[i].damage, 93);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_firethrower, this->playerSet->explosions[i].damage, 93);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_firethrower.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_firethrower, 93);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_firethrower, this->playerSet->lazerbullets[i].damage, 93);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_firethrower, 93);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_firethrower, this->playerSet->lazerbeambullets[i].damage, 93);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_firethrower, this->playerSet->fireworkbullets[i].damage, 93);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_firethrower, this->enemySet->hb_boss_firethrower, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}
	//bullet vs alienship
	else if (enemySet->boss_alien.mode >= 2 && enemySet->boss_alien.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_alien, this->playerSet->lightbullets[i].damage, 94);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_alien, this->playerSet->explosions[i].damage, 94);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_alien.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_alien, 94);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_alien, this->playerSet->lazerbullets[i].damage, 94);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_alien, 94);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_alien, this->playerSet->lazerbeambullets[i].damage, 94);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_alien, this->playerSet->fireworkbullets[i].damage, 94);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_alien, this->enemySet->hb_boss_alien, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}
	//bullet vs labplane
	else if (enemySet->boss_labplane.mode >= 2 && enemySet->boss_labplane.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_labplane, this->playerSet->lightbullets[i].damage, 95);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_labplane, this->playerSet->explosions[i].damage, 95);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_labplane.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_labplane, 95);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_labplane, this->playerSet->lazerbullets[i].damage, 95);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_labplane, 95);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_labplane, this->playerSet->lazerbeambullets[i].damage, 95);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_labplane, this->playerSet->fireworkbullets[i].damage, 95);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_labplane, this->enemySet->hb_boss_labplane, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}
	//bullet vs finalboss
	else if (enemySet->boss_final.mode >= 2 && enemySet->boss_final.mode < 10)
	{
		for (int i = 0; i < MAX_DBULLET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->dbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->dbullets[i], this->playerSet->hb_dbullet))
					enemyDamage(this->playerSet->dbullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_left[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->twbullets_left[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_left[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->twbullets_right[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->twbullets_right[i], this->playerSet->hb_twbullet))
					enemyDamage(this->playerSet->twbullets_right[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->longbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->longbullets[i], this->playerSet->hb_longbullet))
					enemyDamage(this->playerSet->longbullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->shotbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->shotbullets[i], this->playerSet->hb_shotgun))
					enemyDamage(this->playerSet->shotbullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lightbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->lightbullets[i], this->playerSet->hb_lightball))
					enemyDamage(this->enemySet->boss_final, this->playerSet->lightbullets[i].damage, 96);
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->randombullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->randombullets[i], this->playerSet->hb_randombullet))
					enemyDamage(this->playerSet->randombullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->grenadebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->grenadebullets[i], this->playerSet->hb_grenade))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.5;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->grenadebullets[i].position;
					this->playerSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				}
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->explosions[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->explosions[i], this->playerSet->hb_explosion))
					enemyDamage(this->enemySet->boss_final, this->playerSet->explosions[i].damage, 96);
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->firebullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->firebullets[i], this->playerSet->hb_fireshot))
				{
					if (rand() % 100 > 70)
						this->enemySet->boss_final.onFire = rand() % 5;
					enemyDamage(this->playerSet->firebullets[i], this->enemySet->boss_final, 96);
				}
		for (int i = 0; i < MAX_LAZER; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->lazerbullets[i], this->playerSet->hb_lazer))
					enemyDamage(this->enemySet->boss_final, this->playerSet->lazerbullets[i].damage, 96);
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->blastbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->blastbullets[i], this->playerSet->hb_blastshot))
					enemyDamage(this->playerSet->blastbullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_HOMING; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->homingbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->homingbullets[i], this->playerSet->hb_homingshot))
					enemyDamage(this->playerSet->homingbullets[i], this->enemySet->boss_final, 96);
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->lazerbeambullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->lazerbeambullets[i], this->playerSet->hb_lazerbeam))
					enemyDamage(this->enemySet->boss_final, this->playerSet->lazerbeambullets[i].damage, 96);
		for (int i = 0; i < MAX_FIRE_WORK; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->fireworkbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->fireworkbullets[i], this->playerSet->hb_firework))
					enemyDamage(this->enemySet->boss_final, this->playerSet->fireworkbullets[i].damage, 96);
		for (int i = 0; i < MAX_ROCKET; i++)
			if (!this->playerSet->checkOutOfBound(this->playerSet->rocketbullets[i]))
				if (coll.EnemyBulletCollision(this->enemySet->boss_final, this->enemySet->hb_boss_final, this->playerSet->rocketbullets[i], this->playerSet->hb_rocket))
				{
					this->playerSet->explosions[playerSet->avaliableBullet(98)].lifespan = 0.3f;
					this->playerSet->explosions[playerSet->avaliableBullet(98)].position = this->playerSet->rocketbullets[i].position;
					this->playerSet->rocketbullets[i].position = sf::Vector2f(-1800, 0);
					this->playerSet->rocketbullets[i].velocity = sf::Vector2f(0, 0);
				}
	}

	///////////////////////////////////////////////////////
	////////////////////BULLET VS PLAYER///////////////////
	///////////////////////////////////////////////////////
	//default bullet vs player
	for (int i = 0; i < MAX_DBULLET; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->dbullets[i]))
			if (playerDamage(this->enemyBulletSet->dbullets[i], this->enemyBulletSet->hb_dbullet) != 0)
				bulletDisappear(this->enemyBulletSet->dbullets[i]);

	//two way vs player
	for (int i = 0; i < MAX_TWOWAYB; i++)
	{
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->twbullets_left[i]))
			if (playerDamage(this->enemyBulletSet->twbullets_left[i], this->enemyBulletSet->hb_twbullet) != 0)
				bulletDisappear(this->enemyBulletSet->twbullets_left[i]);
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->twbullets_right[i]))
			if (playerDamage(this->enemyBulletSet->twbullets_right[i], this->enemyBulletSet->hb_twbullet) != 0)
				bulletDisappear(this->enemyBulletSet->twbullets_right[i]);
	}

	//long shot vs player
	for (int i = 0; i < MAX_LONGSHOT; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->longbullets[i]))
			if (playerDamage(this->enemyBulletSet->longbullets[i], this->enemyBulletSet->hb_longbullet) != 0)
				bulletDisappear(this->enemyBulletSet->longbullets[i]);

	//shot gun vs player
	for (int i = 0; i < MAX_SHOTGUN; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->shotbullets[i]))
			if (playerDamage(this->enemyBulletSet->shotbullets[i], this->enemyBulletSet->hb_shotgun) != 0)
				bulletDisappear(this->enemyBulletSet->shotbullets[i]);

	//fire bullet vs player
	for (int i = 0; i < MAX_FIRE_BALL; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->firebullets[i]))
		{
			if (playerDamage(this->enemyBulletSet->firebullets[i], this->enemyBulletSet->hb_fireshot) == 1)
			{
				if (rand() % 100 > 70)
					this->player->onFire = rand() % 5;
				bulletDisappear(this->enemyBulletSet->firebullets[i]);
			}
			else if (playerDamage(this->enemyBulletSet->firebullets[i], this->enemyBulletSet->hb_fireshot) == 2)
				bulletDisappear(this->enemyBulletSet->firebullets[i]);
		}
				
	//grenade vs player
	for (int i = 0; i < MAX_GRENADESHOT; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->grenadebullets[i]))
			if (playerDamage(this->enemyBulletSet->grenadebullets[i], this->enemyBulletSet->hb_grenade) != 0)
			{
				this->enemyBulletSet->explosions[enemyBulletSet->avaliableBullet(98)].lifespan = 0.3f;
				this->enemyBulletSet->explosions[enemyBulletSet->avaliableBullet(98)].position = this->enemyBulletSet->grenadebullets[i].position;
				this->enemyBulletSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
				this->enemyBulletSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				bulletDisappear(this->enemyBulletSet->grenadebullets[i]);
			}

	//explosion vs player
	for (int i = 0; i < MAX_EXPLOSION; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->explosions[i]))
			playerDamage(this->enemyBulletSet->explosions[i], this->enemyBulletSet->hb_explosion);

	//homing vs player
	for (int i = 0; i < MAX_HOMING; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->homingbullets[i]))
			if (playerDamage(this->enemyBulletSet->homingbullets[i], this->enemyBulletSet->hb_homingshot) != 0)
				bulletDisappear(this->enemyBulletSet->homingbullets[i]);

	//random vs player
	for (int i = 0; i < MAX_RANDOMSHOT; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->randombullets[i]))
			if (playerDamage(this->enemyBulletSet->randombullets[i], this->enemyBulletSet->hb_randombullet) != 0)
				bulletDisappear(this->enemyBulletSet->randombullets[i]);

	//lightball vs player
	for (int i = 0; i < MAX_LIGHTBALL; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->lightbullets[i]))
			playerDamage(this->enemyBulletSet->lightbullets[i], this->enemyBulletSet->hb_lightball);

	//lazer vs player
	for (int i = 0; i < MAX_LAZER; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->lazerbullets[i]))
			playerDamage(this->enemyBulletSet->lazerbullets[i], this->enemyBulletSet->hb_lazer);

	//blast vs player
	for (int i = 0; i < MAX_BLASTSHOT; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->blastbullets[i]))
			if (playerDamage(this->enemyBulletSet->blastbullets[i], this->enemyBulletSet->hb_blastshot) != 0)
				bulletDisappear(this->enemyBulletSet->blastbullets[i]);

	//lazer beam vs player
	for (int i = 0; i < MAX_LAZER_BEAM; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->lazerbeambullets[i]))
			playerDamage(this->enemyBulletSet->lazerbeambullets[i], this->enemyBulletSet->hb_lazerbeam);

	//firework vs player
	for (int i = 0; i < MAX_FIRE_WORK; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->fireworkbullets[i]))
			if (playerDamage(this->enemyBulletSet->fireworkbullets[i], this->enemyBulletSet->hb_firework) != 0)
				bulletDisappear(this->enemyBulletSet->fireworkbullets[i]);

	//rocket vs player
	for (int i = 0; i < MAX_ROCKET; i++)
		if (!this->enemyBulletSet->checkOutOfBound(this->enemyBulletSet->rocketbullets[i]))
			if (playerDamage(this->enemyBulletSet->rocketbullets[i], this->enemyBulletSet->hb_rocket) != 0)
			{
				this->enemyBulletSet->explosions[enemyBulletSet->avaliableBullet(98)].lifespan = 0.3f;
				this->enemyBulletSet->explosions[enemyBulletSet->avaliableBullet(98)].position = this->enemyBulletSet->rocketbullets[i].position;
				this->enemyBulletSet->grenadebullets[i].position = sf::Vector2f(-1800, 0);
				this->enemyBulletSet->grenadebullets[i].velocity = sf::Vector2f(0, 0);
				bulletDisappear(this->enemyBulletSet->rocketbullets[i]);
			}


	///////////////////////////////////////////////////////
	////////////////////TOOL VS PLAYER/////////////////////
	///////////////////////////////////////////////////////

	//green shield vs player
	for (int i = 0; i < MAX_GREEN_SHIELD; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->shieldTool[i]))
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->shieldTool[i].position, this->toolSet->hb_greenShield.hitbox_r))
			{
				this->record->toolsPicked[0]++;
				this->toolSet->shieldTool[i].position = sf::Vector2f(0, -700);
				this->toolSet->shieldTool[i].velocity = sf::Vector2f(0, 0);
				this->shield->addShield(1);
			}
	}

	//blue shield vs player
	for (int i = 0; i < MAX_BLUE_SHIELD; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->bshieldTool[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->bshieldTool[i].position, this->toolSet->hb_blueShield.hitbox_r))
			{
				this->record->toolsPicked[2]++;
				this->toolSet->bshieldTool[i].position = sf::Vector2f(0, -700);
				this->toolSet->bshieldTool[i].velocity = sf::Vector2f(0, 0);
				this->player->addShield(80);
			}
		}
	}

	//yellow shield vs player
	for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->yshieldTool[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->yshieldTool[i].position, this->toolSet->hb_blueShield.hitbox_r))
			{
				this->record->toolsPicked[1]++;
				this->toolSet->yshieldTool[i].position = sf::Vector2f(0, -700);
				this->toolSet->yshieldTool[i].velocity = sf::Vector2f(0, 0);
				this->radShield->addShield(50);
			}
		}
	}

	//health pack vs player
	for (int i = 0; i < MAX_HEALTH_PACK; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->healthpack[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->healthpack[i].position, this->toolSet->hb_healthPack.hitbox_r))
			{
				this->record->toolsPicked[3]++;
				this->toolSet->healthpack[i].position = sf::Vector2f(0, -700);
				this->toolSet->healthpack[i].velocity = sf::Vector2f(0, 0);
				this->player->hp += 50;
				if (this->player->hp >= this->player->maxhp) this->player->hp = this->player->maxhp;
			}
		}
	}

	//imumium vs player 
	for (int i = 0; i < MAX_IMUMIUM; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->imumium[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->imumium[i].position, this->toolSet->hb_imumium.hitbox_r))
			{
				this->record->toolsPicked[4]++;
				this->toolSet->imumium[i].position = sf::Vector2f(0, -700);
				this->toolSet->imumium[i].velocity = sf::Vector2f(0, 0);
				this->player->holdbuff += 10000;
				this->player->CURRENT_HOLD_BULLET = MAX_HOLD_BULLET;
			}
		}
	}

	//stone vs player
	for (int i = 0; i < MAX_STONE; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->stoneTool[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->stoneTool[i].position, this->toolSet->hb_stone.hitbox_r))
			{
				this->record->toolsPicked[5]++;
				this->toolSet->stoneTool[i].position = sf::Vector2f(0, -700);
				this->toolSet->stoneTool[i].velocity = sf::Vector2f(0, 0);
				this->player->onLuck += 15000;
				this->droprate->multiplier = 1.5f;
			}
		}
	}

	//clock vs player
	for (int i = 0; i < MAX_CLOCK; i++)
	{
		if (!this->toolSet->checkOutOfBound(this->toolSet->clocksTool[i]))
		{
			if (coll.RectangleCircleCollision(sf::Vector2f(this->player->position + this->player->hb.hitbox_tl), sf::Vector2f(this->player->position + this->player->hb.hitbox_br),
				this->toolSet->clocksTool[i].position, this->toolSet->hb_clock.hitbox_r))
			{
				this->toolSet->clocksTool[i].position = sf::Vector2f(0, -700);
				this->toolSet->clocksTool[i].velocity = sf::Vector2f(0, 0);
				this->enemySet->isFreeze += 2000;
			}
		}
	}
}

void Model::checkDie(Enemy& enemy, int type)
{
	if (enemy.hp <= 0)
	{
		switch (type)
		{
		case 1:
			enemyDie(enemy, this->enemyBulletSet->dbullets[0], 1, 10, 8);
			break;
		case 2:
			enemyDie(enemy, this->enemyBulletSet->twbullets_left[0], 2, 15, 10);
			break;
		case 3:
			enemyDie(enemy, this->enemyBulletSet->longbullets[0], 3, 30, 15);
			break;
		case 4:
			enemyDie(enemy, this->enemyBulletSet->shotbullets[0], 4, 50, 20);
			break;
		case 5:
			enemyDie(enemy, this->enemyBulletSet->firebullets[0], 8, 30, 15);
			break;
		case 6:
			enemyDie(enemy, this->enemyBulletSet->grenadebullets[0], 7, 50, 20);
			break;
		case 7:
			enemyDie(enemy, this->enemyBulletSet->homingbullets[0], 11, 50, 30);
			break;
		case 8:
			enemyDie(enemy, this->enemyBulletSet->randombullets[0], 6, 20, 25);
			break;
		case 9:
			enemyDie(enemy, this->enemyBulletSet->lightbullets[0], 5, 30, 10);
			break;
		case 10:
			enemyDie(enemy, this->enemyBulletSet->lazerbullets[0], 9, 50, 30);
			break;
		case 91:
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 3].position = sf::Vector2f(-3000, 0);
			enemyDie(enemy, this->enemyBulletSet->lazerbullets[0], 9, 1000, 100);
			enemySet->current_boss = 0;
			break;
		case 92:
			enemyDie(enemy, this->enemyBulletSet->blastbullets[0], 10, 1500, 100);
			enemySet->current_boss = 0;
			break;
		case 93:
			enemyDie(enemy, this->enemyBulletSet->firerootbullets[0], 13, 3000, 100);
			enemySet->current_boss = 0;
			break;
		case 94:
			enemyDie(enemy, this->enemyBulletSet->blastbullets[0], 10, 3000, 100);
			enemySet->current_boss = 0;
			break;
		case 95:
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 1].position = sf::Vector2f(-3000, 0);
			this->enemyBulletSet->lazerbullets[MAX_LAZER - 2].position = sf::Vector2f(-3000, 0);
			enemyDie(enemy, this->enemyBulletSet->rocketbullets[0], 14, 4000, 100);
			enemySet->current_boss = 0;
			break;
		case 96:
			this->enemyBulletSet->lazerbeambullets[MAX_LAZER_BEAM - 1].position = sf::Vector2f(-3000, 0);
			enemyDie(enemy, this->enemyBulletSet->lazerbeambullets[0], 12, 5000, 100);
			enemySet->current_boss = 0;
			break;
		case 11:
			switch (rand() % 5)
			{
			case 0:
				enemyDie(enemy, this->enemyBulletSet->lazerbullets[0], 9, 0, 0);
				break;
			case 1:
				enemyDie(enemy, this->enemyBulletSet->blastbullets[0], 10, 0, 0);
				break;
			case 2:
				enemyDie(enemy, this->enemyBulletSet->firerootbullets[0], 13, 0, 0);
				break;
			case 3:
				enemyDie(enemy, this->enemyBulletSet->lightbullets[0], 5, 0, 0);
				break;
			case 4:
				enemyDie(enemy, this->enemyBulletSet->grenadebullets[0], 7, 0, 0);
				break;
			}
			break;
		}
	}
}

void Model::enemyDie(Enemy& enemy, Bullet& bullet, int bullet_type, int score_add, int shield_add)
{
	//dropping 
	tool_type = rand() % NUM_OF_TOOLS + 1;
	if (rand() % 100 < droprate->getToolChance(tool_type))
		this->toolSet->drop(enemy, tool_type);
	/*
	if (rand() % 100 < droprate->getToolChance(1))
		this->toolSet->drop(enemy, 1);
	else if (rand() % 100 < droprate->getToolChance(2))
		this->toolSet->drop(enemy, 2);
	else  if (rand() % 100 < droprate->getToolChance(3))
		this->toolSet->drop(enemy, 3);
	else if (rand() % 100 < droprate->getToolChance(4))
		this->toolSet->drop(enemy, 4);
	else if (rand() % 100 < droprate->getToolChance(5))
		this->toolSet->drop(enemy, 5);
	else if (rand() % 100 < droprate->getToolChance(6))
		this->toolSet->drop(enemy, 6);
		*/


	//enemy reset
	Boss* isBoss = dynamic_cast<Boss*>(&enemy);
	if (isBoss)
	{
		if (isBoss->mode != 10)
		{
			isBoss->mode = 10;
			this->player->addBullet(bullet_type, bullet.shoot_rate);
			this->player->addShield(shield_add);
			this->player->score += score_add;
			this->record->bossDefeated++;
		}
		
	}
	else
	{
		enemy.hp = enemy.maxhp;
		enemy.position = sf::Vector2f(0, 100000);
		enemy.velocity = sf::Vector2f(0, 0);
		this->player->addBullet(bullet_type, bullet.shoot_rate);
		this->player->addShield(shield_add);
		this->player->score += score_add;
	}
	enemy.onFire = 0;
}

int Model::playerDamage(Bullet& bullet, Hitbox& hitbox)
{
	if (this->shield->level != 0 || this->radShield->health != 0)
	{
		if (this->shield->hitbox.hitbox_r > this->radShield->hitbox.hitbox_r)
		{
			if (coll.ShieldBulletCollision(this->player, this->shield->hitbox.hitbox_r, bullet, hitbox))
			{
				//shield is being destroyed
				this->shield->addShield(-1);
				return 2;
			}
		}
		else
		{
			if (coll.ShieldBulletCollision(this->player, this->radShield->hitbox.hitbox_r, bullet, hitbox))
			{
				//shield is being damaged
				this->radShield->addShield(-bullet.damage * 0.75f);
				return 2;
			}
		}
	}
	else
	{
		if (coll.PlayerBulletCollision(this->player, bullet, hitbox))
		{
			//player is being damaged
			if (this->player->shield > 0) this->player->shield -= bullet.damage;
			else this->player->hp -= bullet.damage;
			return 1;
		}
	}
	return 0;
}

void Model::bulletDisappear(Bullet& bullet)
{
	bullet.position = sf::Vector2f(-1800, 0);
	bullet.velocity = sf::Vector2f(0, 0);
}

void Model::enemyDamage(Bullet& bullet, Enemy& enemy, int type)
{
	//enemy is being damaged
	enemy.hp -= bullet.damage;
	//bullet should be disappeared
	bullet.position = sf::Vector2f(-800, 0);
	bullet.velocity = sf::Vector2f(0, 0);
	//check if the enemy die
	checkDie(enemy, type);
}

void Model::enemyDamage(Enemy& enemy, int damage, int type)
{
	//enemy is being damaged
	enemy.hp -= damage;
	//check if the enemy die
	checkDie(enemy, type);
}

//homing bullet will target enemy within 300 pixels 
sf::Vector2f Model::findTarget(sf::Vector2f& position)
{
	int minitype = 0;
	int minimum = -1;
	float minid = 100000000;

	float distance;

	for (int i = 0; i < MAX_DENEMY; i++)
	{
		distance = pow(enemySet->denemies[i].position.x - position.x, 2) + pow(enemySet->denemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 1;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->douenemies[i].position.x - position.x, 2) + pow(enemySet->douenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 2;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->lonenemies[i].position.x - position.x, 2) + pow(enemySet->lonenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 3;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->shotenemies[i].position.x - position.x, 2) + pow(enemySet->shotenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 4;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->gangenemies[i].position.x - position.x, 2) + pow(enemySet->gangenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 5;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->thugenemies[i].position.x - position.x, 2) + pow(enemySet->thugenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 6;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->unknownenemies[i].position.x - position.x, 2) + pow(enemySet->unknownenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 7;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->glitchyenemies[i].position.x - position.x, 2) + pow(enemySet->glitchyenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 8;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->advancedenemies[i].position.x - position.x, 2) + pow(enemySet->advancedenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 9;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->lazzyenemies[i].position.x - position.x, 2) + pow(enemySet->lazzyenemies[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 10;
			minimum = i;
			minid = distance;
		}
		distance = pow(enemySet->friendShips[i].position.x - position.x, 2) + pow(enemySet->friendShips[i].position.y - position.y, 2);
		if (distance < minid)
		{
			minitype = 11;
			minimum = i;
			minid = distance;
		}
	}

	if (minid <= 90000)
		switch (minitype)
		{
		case 1:
			return enemySet->denemies[minimum].position;
		case 2:
			return enemySet->douenemies[minimum].position;
		case 3:
			return enemySet->lonenemies[minimum].position;
		case 4:
			return enemySet->shotenemies[minimum].position;
		case 5:
			return enemySet->gangenemies[minimum].position;
		case 6:
			return enemySet->thugenemies[minimum].position;
		case 7:
			return enemySet->unknownenemies[minimum].position;
		case 8:
			return enemySet->glitchyenemies[minimum].position;
		case 9:
			return enemySet->advancedenemies[minimum].position;
		case 10:
			return enemySet->lazzyenemies[minimum].position;
		case 11:
			return enemySet->friendShips[minimum].position;
		}
	return sf::Vector2f(-1, -1);
}