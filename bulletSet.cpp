#include "bulletSet.hpp"

BulletSet::BulletSet(int isPlayer) {
	this->isPlayer = isPlayer;

	hb_dbullet.hitbox_r = 7.f;
	hb_dbullet.generateHitboxCir();

	hb_twbullet.hitbox_r = 7.f;
	hb_twbullet.generateHitboxCir();

	hb_longbullet.hitbox_tl = sf::Vector2f(0, 0);
	hb_longbullet.hitbox_br = sf::Vector2f(12, 62);
	hb_longbullet.generateHitboxRec();

	hb_shotgun.hitbox_r = 2.5f;
	hb_shotgun.generateHitboxCir();

	hb_lightball.hitbox_r = 15.f;
	hb_lightball.generateHitboxCir();


	hb_randombullet.hitbox_r = 5.f;
	hb_randombullet.generateHitboxCir();

	hb_grenade.hitbox_r = 10.f;
	hb_grenade.generateHitboxCir();

	hb_explosion.hitbox_r = 50.f;
	hb_explosion.generateHitboxCir();

	if (isPlayer == 1)
	{
		hb_fireshot.hitbox_tl = sf::Vector2f(0, 0);
		hb_fireshot.hitbox_br = sf::Vector2f(15, 15);
		hb_fireshot.generateHitboxRec();
	}
	else
	{
		hb_fireshot.hitbox_tl = sf::Vector2f(6, 38);
		hb_fireshot.hitbox_br = sf::Vector2f(20, 52);
		hb_fireshot.generateHitboxRec();
	}

	//lazer bullet
	if (isPlayer == 1)
	{
		hb_lazer.hitbox_tl = sf::Vector2f(7 - 2.5f, -SCREEN_HEIGHT);
		hb_lazer.hitbox_br = sf::Vector2f(12 - 2.5f, 0);
	}
	else
	{
		hb_lazer.hitbox_tl = sf::Vector2f(7 - 2.5f, 0);
		hb_lazer.hitbox_br = sf::Vector2f(12 - 2.5f, SCREEN_HEIGHT);
	}
	hb_lazer.generateHitboxRec();
	for (int i = 0; i < MAX_LAZER; i++)
		if (isPlayer == 1)
			lazerbullets[i].isPlayer = true;
		else
			lazerbullets[i].isPlayer = false;

	hb_blastshot.hitbox_r = 4.f;
	hb_blastshot.generateHitboxCir();

	hb_homingshot.hitbox_r = 4.f;
	hb_homingshot.generateHitboxCir();

	hb_lazerbeam.hitbox_tl = sf::Vector2f(15 - 60, -SCREEN_HEIGHT);
	hb_lazerbeam.hitbox_br = sf::Vector2f(134 - 60, 0);
	hb_lazerbeam.generateHitboxRec();

	initBullet();
}

BulletSet::~BulletSet() {}

void BulletSet::update(sf::Time delta_time)
{
	for (int i = 0; i < MAX_DBULLET; i++)
		dbullets[i].update(delta_time);
	for (int i = 0; i < MAX_TWOWAYB; i++)
		twbullets_left[i].update(delta_time);
	for (int i = 0; i < MAX_TWOWAYB; i++)
		twbullets_right[i].update(delta_time);
	for (int i = 0; i < MAX_LONGSHOT; i++)
		longbullets[i].update(delta_time);
	for (int i = 0; i < MAX_SHOTGUN; i++)
		if (!checkOutOfBound(shotbullets[i]))
			shotbullets[i].update(delta_time);	
	for (int i = 0; i < MAX_LIGHTBALL; i++)
		lightbullets[i].update(delta_time);
	for (int i = 0; i < MAX_RANDOMSHOT; i++)
		randombullets[i].update(delta_time);
	for (int i = 0; i < MAX_GRENADESHOT; i++)
		grenadebullets[i].update(delta_time); 
	for (int i = 0; i < MAX_EXPLOSION; i++)
		explosions[i].update(delta_time);
	for (int i = 0; i < MAX_FIRE_BALL; i++)
		firebullets[i].update(delta_time);
	for (int i = 0; i < MAX_LAZER; i++)
		lazerbullets[i].update(delta_time);
	for (int i = 0; i < MAX_BLASTSHOT; i++)
		blastbullets[i].update(delta_time);
	for (int i = 0; i < MAX_HOMING; i++)
		if (!checkOutOfBound(homingbullets[i]))
			homingbullets[i].update(delta_time);
	for (int i = 0; i < MAX_LAZER_BEAM; i++)
		lazerbeambullets[i].update(delta_time);
}

void BulletSet::render(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_DBULLET; i++)
		if (!(checkOutOfBound(dbullets[i])))
			dbullets[i].render(window, sprite_dbullet);
	
	for (int i = 0; i < MAX_TWOWAYB; i++)
	{
		if (!(checkOutOfBound(twbullets_left[i])))
			twbullets_left[i].render(window, sprite_twbullet_left);
		if (!(checkOutOfBound(twbullets_right[i])))
			twbullets_right[i].render(window, sprite_twbullet_right);
	}
	for (int i = 0; i < MAX_LONGSHOT; i++)
		if (!(checkOutOfBound(longbullets[i])))
			longbullets[i].render(window,  sprite_longbullet);
	
	for (int i = 0; i < MAX_SHOTGUN; i++)
		if (!(checkOutOfBound(shotbullets[i])))
			shotbullets[i].render(window, sprite_shotbullet);

	for (int i = 0; i < MAX_LIGHTBALL; i++)
		if (!(checkOutOfBound(lightbullets[i])))
			lightbullets[i].render(window, sprite_lightball);

	for (int i = 0; i < MAX_RANDOMSHOT; i++)
		if (!(checkOutOfBound(randombullets[i])))
			randombullets[i].render(window, sprite_randombullet);

	for (int i = 0; i < MAX_GRENADESHOT; i++)
		if (!(checkOutOfBound(grenadebullets[i])))
			grenadebullets[i].render(window, sprite_grenadebullet);

	for (int i = 0; i < MAX_EXPLOSION; i++)
		if (!(checkOutOfBound(explosions[i])))
			explosions[i].render(window, sprite_explosion);

	for (int i = 0; i < MAX_FIRE_BALL; i++)
		if (!(checkOutOfBound(firebullets[i])))
			firebullets[i].render(window, sprite_fireball);

	for (int i = 0; i < MAX_LAZER; i++)
		if (!(checkOutOfBound(lazerbullets[i])))
			lazerbullets[i].render(window, sprite_lazer);

	for (int i = 0; i < MAX_BLASTSHOT; i++)
		if (!(checkOutOfBound(blastbullets[i])))
			blastbullets[i].render(window, sprite_blastshot);

	for (int i = 0; i < MAX_HOMING; i++)
		if (!(checkOutOfBound(homingbullets[i])))
			homingbullets[i].render(window, sprite_homingshot);

	for (int i = 0; i < MAX_LAZER_BEAM; i++)
		if (!(checkOutOfBound(lazerbeambullets[i])))
			lazerbeambullets[i].render(window, sprite_lazerbeam);
}

void BulletSet::renderHitBox(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_DBULLET; i++)
	{
		if (!(checkOutOfBound(dbullets[i])))
		{
			hb_dbullet.cir.setPosition(dbullets[i].position);
			window.draw(hb_dbullet.cir);
		}
	}
	for (int i = 0; i < MAX_TWOWAYB; i++)
	{
		if (!(checkOutOfBound(twbullets_left[i])))
		{
			hb_twbullet.cir.setPosition(twbullets_left[i].position);
			window.draw(hb_twbullet.cir);
		}
		if (!(checkOutOfBound(twbullets_right[i])))
		{
			hb_twbullet.cir.setPosition(twbullets_right[i].position);
			window.draw(hb_twbullet.cir);
		}
	}
	for (int i = 0; i < MAX_LONGSHOT; i++)
	{
		if (!(checkOutOfBound(longbullets[i])))
		{
			hb_longbullet.rec.setPosition(sf::Vector2f(longbullets[i].position.x + hb_longbullet.hitbox_tl.x, longbullets[i].position.y + hb_longbullet.hitbox_tl.y));
			window.draw(hb_longbullet.rec);
		}
	}
	for (int i = 0; i < MAX_SHOTGUN; i++)
	{
		if (!(checkOutOfBound(shotbullets[i])))
		{
			hb_shotgun.cir.setPosition(shotbullets[i].position);
			window.draw(hb_shotgun.cir);
		}
	}
	for (int i = 0; i < MAX_LIGHTBALL; i++)
	{
		if (!(checkOutOfBound(lightbullets[i])))
		{
			hb_lightball.cir.setPosition(lightbullets[i].position);
			window.draw(hb_lightball.cir);
		}
	}
	for (int i = 0; i < MAX_RANDOMSHOT; i++)
	{
		if (!(checkOutOfBound(randombullets[i])))
		{
			hb_randombullet.cir.setPosition(randombullets[i].position);
			window.draw(hb_randombullet.cir);

		}
	}
	for (int i = 0; i < MAX_GRENADESHOT; i++)
	{
		if (!(checkOutOfBound(grenadebullets[i])))
		{
			hb_grenade.cir.setPosition(grenadebullets[i].position);
			window.draw(hb_grenade.cir);
		}
	}
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (!(checkOutOfBound(explosions[i])))
		{
			hb_explosion.cir.setPosition(explosions[i].position);
			window.draw(hb_explosion.cir);
		}
	}
	for (int i = 0; i < MAX_FIRE_BALL; i++)
	{
		if (!(checkOutOfBound(firebullets[i])))
		{
			hb_fireshot.rec.setPosition(sf::Vector2f(firebullets[i].position.x + hb_fireshot.hitbox_tl.x, firebullets[i].position.y + hb_fireshot.hitbox_tl.y));
			window.draw(hb_fireshot.rec);
		}
	}
	for (int i = 0; i < MAX_LAZER; i++)
	{
		if (!(checkOutOfBound(lazerbullets[i])))
		{
			if (isPlayer == 1)
				hb_lazer.rec.setPosition(lazerbullets[i].position.x - 2.5f, lazerbullets[i].position.y - SCREEN_HEIGHT);
			else
				hb_lazer.rec.setPosition(lazerbullets[i].position.x - 2.5f, lazerbullets[i].position.y);
			window.draw(hb_lazer.rec);
		}
	}
	for (int i = 0; i < MAX_BLASTSHOT; i++)
	{
		if (!(checkOutOfBound(blastbullets[i])))
		{
			hb_blastshot.cir.setPosition(blastbullets[i].position);
			window.draw(hb_blastshot.cir);
		}
	}
	for (int i = 0; i < MAX_HOMING; i++)
	{
		if (!(checkOutOfBound(homingbullets[i])))
		{
			hb_homingshot.cir.setPosition(homingbullets[i].position);
			window.draw(hb_homingshot.cir);
		}
	}
	for (int i = 0; i < MAX_LAZER_BEAM; i++)
	{
		if (!(checkOutOfBound(lazerbeambullets[i])))
		{
			hb_lazerbeam.rec.setPosition(lazerbeambullets[i].position.x - 60, lazerbeambullets[i].position.y - SCREEN_HEIGHT);
			window.draw(hb_lazerbeam.rec);
		}
	}
}

void BulletSet::shoot(int type, sf::Vector2f position, int direction)
{
	float angle = rand() % 360;
	switch(type)
	{
	case 1:
		dbullets[avaliableBullet(type)].velocity.y = direction * dbullets[0].speed;
		if (direction == -1)
			dbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
		else
			dbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 31, position.y + 61);
		break;
	case 2:
		twbullets_left[avaliableBullet(type)].velocity = sf::Vector2f(-400, direction * twbullets_left[0].speed);
		twbullets_right[avaliableBullet(99)].velocity = sf::Vector2f(400, direction * twbullets_right[0].speed);
		if (direction == -1)
		{
			twbullets_left[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
			twbullets_right[avaliableBullet(99)].position = sf::Vector2f(position.x + 36, position.y + 6);
		}
		else
		{
			twbullets_left[avaliableBullet(type)].position = sf::Vector2f(position.x + 10, position.y + 47);
			twbullets_right[avaliableBullet(99)].position = sf::Vector2f(position.x + 39, position.y + 47);
		}
		break;
	case 3:
		longbullets[avaliableBullet(type)].velocity.y = direction * longbullets[0].speed;
		if (direction == -1)
			longbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 30, position.y + 10);
		else
			longbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 10, position.y + 33);
		break;
	case 4:
		for (int i = 0; i < SHOT_GUN_NUMBERS; i++)
		{
			shotbullets[avaliableBullet(type)].velocity.x = (rand() % 600) - 300;
			shotbullets[avaliableBullet(type)].velocity.y = direction * shotbullets[0].speed;
			shotbullets[avaliableBullet(type)].lifespan = (rand() % 5) / 20.f + 0.2;
			if (direction == -1)
				shotbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
			else
				shotbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 20);
		}
		break;
	case 5:
		lightbullets[avaliableBullet(type)].velocity.y = direction * lightbullets[0].speed;
		if (direction == -1)
			lightbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 10);
		else
			lightbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 16, position.y + 47);
		break;
	case 6:
		randombullets[avaliableBullet(type)].velocity.y = randombullets[0].speed * sin(angle);
		randombullets[avaliableBullet(type)].velocity.x = randombullets[0].speed * cos(angle);
		if (direction == -1)
			randombullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
		else
			randombullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 22, position.y + 22);
		break;
	case 7:
		grenadebullets[avaliableBullet(type)].velocity.y = direction * grenadebullets[0].speed;
		if (direction == -1)
			grenadebullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 8);
		else
			grenadebullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 56, position.y + 44);
		break;
	case 8:
		firebullets[avaliableBullet(type)].velocity.y = direction * firebullets[0].speed;
		if (direction == -1)
			firebullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 29, position.y + 10);
		else
			firebullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 20, position.y + 0);
		break;
	case 9:
		lazerbullets[avaliableBullet(type)].lifespan = 0.3;
		if (direction == -1)
			lazerbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 26);
		else
			lazerbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 17, position.y + 52);
		break;
	case 10:
		for (int i = 2; i < BLAST_SHOT_NUMBERS; i++)
		{
			blastbullets[avaliableBullet(type)].velocity.y = direction * blastbullets[0].speed * sin((i * 7.5f) * 3.14f / 180.f);
			blastbullets[avaliableBullet(type)].velocity.x = direction * blastbullets[0].speed * cos((i * 7.5f) * 3.14f / 180.f);
			if (direction == -1)
				blastbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
		}
		break;
	case 11:
		homingbullets[avaliableBullet(type)].velocity = sf::Vector2f(0, direction * homingbullets[0].speed);
		//homingbullets[avaliableBullet(type)].target = sf::Vector2f(300, 300);
		if (direction == -1)
		{
			homingbullets[avaliableBullet(type)].angle = 200;
			homingbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
		}
		else
		{
			homingbullets[avaliableBullet(type)].angle = -200;
			homingbullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 34, position.y + 60);
		}
		break;
	case 12:
		lazerbeambullets[avaliableBullet(type)].lifespan = 1.8f;
		if (direction == -1)
			lazerbeambullets[avaliableBullet(type)].position = sf::Vector2f(position.x + 36, position.y + 6);
		//else
			//lazerbeambullets[avaliableBullet(type)]
		break;
	}
}

//99 -> twbullet right
void BulletSet::shoot(int type, sf::Vector2f position)
{
	switch (type)
	{
	case 1:
		dbullets[avaliableBullet(type)].velocity.y = dbullets[0].speed;
		dbullets[avaliableBullet(type)].position = position;
		break;
	case 2:
		twbullets_left[avaliableBullet(type)].velocity = sf::Vector2f(-400, twbullets_left[0].speed);
		twbullets_left[avaliableBullet(type)].position = position;
		break;
	case 3:
		longbullets[avaliableBullet(type)].velocity.y = longbullets[0].speed;
		longbullets[avaliableBullet(type)].position = position;
		break;
	case 4:
		for (int i = 0; i < SHOT_GUN_NUMBERS; i++)
		{
			shotbullets[avaliableBullet(type)].velocity.x = (rand() % 600) - 300;
			shotbullets[avaliableBullet(type)].velocity.y = shotbullets[0].speed;
			shotbullets[avaliableBullet(type)].lifespan = (rand() % 5) / 20.f + 0.2;
			shotbullets[avaliableBullet(type)].position = position;
		}
		break;
	case 99:
		twbullets_right[avaliableBullet(type)].velocity = sf::Vector2f(400, twbullets_right[0].speed);
		twbullets_right[avaliableBullet(type)].position = position;
		break;
	case 10:
		for (int i = 2; i < BLAST_SHOT_NUMBERS; i++)
		{
			blastbullets[avaliableBullet(type)].velocity.y = blastbullets[0].speed * sin((i * 15) * 3.14f / 180.f);
			blastbullets[avaliableBullet(type)].velocity.x = blastbullets[0].speed * cos((i * 15) * 3.14f / 180.f);
			blastbullets[avaliableBullet(type)].position = position;
		}
		break;
	}
}

void BulletSet::initBullet()
{
	for (int i = 0; i < MAX_DBULLET; i++)
		dbullets[i].position = sf::Vector2f(-1800, 0);
	
	for (int i = 0; i < MAX_TWOWAYB; i++)
	{
		twbullets_left[i].position = sf::Vector2f(-1800, 0);
		twbullets_right[i].position = sf::Vector2f(-1800, 0);
	}
	for (int i = 0; i < MAX_LONGSHOT; i++)
		longbullets[i].position = sf::Vector2f(-1800, 0);
	
	for (int i = 0; i < MAX_SHOTGUN; i++)
		shotbullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_LIGHTBALL; i++)
		lightbullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_RANDOMSHOT; i++)
		randombullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_GRENADESHOT; i++)
		grenadebullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_EXPLOSION; i++)
		explosions[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_FIRE_BALL; i++)
		firebullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_LAZER; i++)
		lazerbullets[i].position = sf::Vector2f(-3000, 0);
	
	for (int i = 0; i < MAX_BLASTSHOT; i++)
		blastbullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_HOMING; i++)
		homingbullets[i].position = sf::Vector2f(-1800, 0);

	for (int i = 0; i < MAX_LAZER_BEAM; i++)
		lazerbeambullets[i].position = sf::Vector2f(-3000, 0);
}

bool BulletSet::checkOutOfBound(Bullet& b)
{
	if (b.position.x < -100) return true;
	if (b.position.x > SCREEN_WIDTH + 100) return true;
	if (b.position.y < -100) return true;
	if (b.position.y > SCREEN_HEIGHT + 100) return true;
	return false;
}

//number 99 -> twoway bullet right
//number 98 -> explosion
int BulletSet::avaliableBullet(int type)
{
	switch (type)
	{
	case 1:
		for (int i = 0; i < MAX_DBULLET; i++)
			if (checkOutOfBound(dbullets[i]))
				return i;
		return 0;
	case 2:
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (checkOutOfBound(twbullets_left[i]))
				return i;
		return 0;
	case 99:
		for (int i = 0; i < MAX_TWOWAYB; i++)
			if (checkOutOfBound(twbullets_right[i]))
				return i;
		return 0;
	case 3:
		for (int i = 0; i < MAX_LONGSHOT; i++)
			if (checkOutOfBound(longbullets[i]))
				return i;
		return 0;
	case 4:
		for (int i = 0; i < MAX_SHOTGUN; i++)
			if (checkOutOfBound(shotbullets[i]))
				return i;
		return 0;
	case 5:
		for (int i = 0; i < MAX_LIGHTBALL; i++)
			if (checkOutOfBound(lightbullets[i]))
				return i;
		return 0;
	case 6:
		for (int i = 0; i < MAX_RANDOMSHOT; i++)
			if (checkOutOfBound(randombullets[i]))
				return i;
		return 0;
	case 7:
		for (int i = 0; i < MAX_GRENADESHOT; i++)
			if (checkOutOfBound(grenadebullets[i]))
				return i;
		return 0;
	case 98:
		for (int i = 0; i < MAX_EXPLOSION; i++)
			if (checkOutOfBound(explosions[i]))
				return i;
		return 0;
	case 8:
		for (int i = 0; i < MAX_FIRE_BALL; i++)
			if (checkOutOfBound(firebullets[i]))
				return i;
		return 0;
	case 9:
		for (int i = 0; i < MAX_LAZER; i++)
			if (checkOutOfBound(lazerbullets[i]))
				return i;
		return 0;
	case 10:
		for (int i = 0; i < MAX_BLASTSHOT; i++)
			if (checkOutOfBound(blastbullets[i]))
				return i;
		return 0;
	case 11:
		for (int i = 0; i < MAX_HOMING; i++)
			if (checkOutOfBound(homingbullets[i]))
				return i;
		return 0;
	case 12:
		for (int i = 0; i < MAX_LAZER_BEAM; i++)
			if (checkOutOfBound(lazerbeambullets[i]))
				return i;
		return 0;
	}
	return 0;
}