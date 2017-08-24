#include "enemyset.hpp"

EnemySet::EnemySet()
{
	//enemies hitbox
	hb_denemy.hitbox_tl = sf::Vector2f(0, 0);
	hb_denemy.hitbox_br = sf::Vector2f(62, 62);
	hb_denemy.generateHitboxRec();

	hb_douenemy.hitbox_tl = sf::Vector2f(3, 3);
	hb_douenemy.hitbox_br = sf::Vector2f(45, 60);
	hb_douenemy.generateHitboxRec();

	hb_longenemy.hitbox_tl = sf::Vector2f(0, 0);
	hb_longenemy.hitbox_br = sf::Vector2f(32, 64);
	hb_longenemy.generateHitboxRec();

	hb_shotenemy.hitbox_tl = sf::Vector2f(0, 0);
	hb_shotenemy.hitbox_br = sf::Vector2f(72, 24);
	hb_shotenemy.generateHitboxRec();

	hb_gangenemy.hitbox_tl = sf::Vector2f(8, 6);
	hb_gangenemy.hitbox_br = sf::Vector2f(55, 37);
	hb_gangenemy.generateHitboxRec();

	hb_thugenemy.hitbox_tl = sf::Vector2f(0, 8);
	hb_thugenemy.hitbox_br = sf::Vector2f(64, 34);
	hb_thugenemy.generateHitboxRec();

	hb_unknownenemy.hitbox_tl = sf::Vector2f(18, 18);
	hb_unknownenemy.hitbox_br = sf::Vector2f(51, 64);
	hb_unknownenemy.generateHitboxRec();

	hb_glitchyenemy.hitbox_tl = sf::Vector2f(3, 3);
	hb_glitchyenemy.hitbox_br = sf::Vector2f(42, 37);
	hb_glitchyenemy.generateHitboxRec();

	hb_advancedenemy.hitbox_tl = sf::Vector2f(3, 0);
	hb_advancedenemy.hitbox_br = sf::Vector2f(29, 58);
	hb_advancedenemy.generateHitboxRec();

	hb_lazzyenemy.hitbox_tl = sf::Vector2f(0, 0);
	hb_lazzyenemy.hitbox_br = sf::Vector2f(35, 35);
	hb_lazzyenemy.generateHitboxRec();

	//boss hitbox
	hb_boss_devplane.hitbox_tl = sf::Vector2f(0, 90);
	hb_boss_devplane.hitbox_br = sf::Vector2f(560, 292);
	hb_boss_devplane.generateHitboxRec();

	hb_boss_modifier.hitbox_tl = sf::Vector2f(0, 97);
	hb_boss_modifier.hitbox_br = sf::Vector2f(576, 339);
	hb_boss_modifier.generateHitboxRec();

	hb_boss_firethrower.hitbox_tl = sf::Vector2f(0, 65);
	hb_boss_firethrower.hitbox_br = sf::Vector2f(548, 245);
	hb_boss_firethrower.generateHitboxRec();

	hb_boss_alien.hitbox_tl = sf::Vector2f(12, 62);
	hb_boss_alien.hitbox_br = sf::Vector2f(546, 271);
	hb_boss_alien.generateHitboxRec();

	hb_boss_labplane.hitbox_tl = sf::Vector2f(92, 8);
	hb_boss_labplane.hitbox_br = sf::Vector2f(467, 381);
	hb_boss_labplane.generateHitboxRec();

	hb_boss_final.hitbox_tl = sf::Vector2f(105, 194);
	hb_boss_final.hitbox_br = sf::Vector2f(467, 380);
	hb_boss_final.generateHitboxRec();

	initEnemy();
}

EnemySet::~EnemySet() {}

void EnemySet::update(sf::Time delta_time)
{
	//updating enemies
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		denemies[i].update(delta_time);
		douenemies[i].update(delta_time);
		lonenemies[i].update(delta_time);
		shotenemies[i].update(delta_time);
		gangenemies[i].update(delta_time);
		thugenemies[i].update(delta_time);
		unknownenemies[i].update(delta_time);
		glitchyenemies[i].update(delta_time);
		advancedenemies[i].update(delta_time);
		lazzyenemies[i].update(delta_time);
	}

	//updating boss
	if (!checkOutOfBound(boss_devplane))
		boss_devplane.update(delta_time);
	if (!checkOutOfBound(boss_modifier))
		boss_modifier.update(delta_time);
	if (!checkOutOfBound(boss_firethrower))
		boss_firethrower.update(delta_time);
	if (!checkOutOfBound(boss_alien))
		boss_alien.update(delta_time);
	if (!checkOutOfBound(boss_labplane))
		boss_labplane.update(delta_time);
	if (!checkOutOfBound(boss_final))
		boss_final.update(delta_time);

	pushBack(delta_time);
}

void EnemySet::render(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		//enemies render
		if (!(checkOutOfBound(denemies[i])))
			denemies[i].render(window, sprite_denemy);
		if (!(checkOutOfBound(douenemies[i])))
			douenemies[i].render(window, sprite_douenemy);
		if (!(checkOutOfBound(lonenemies[i])))
			lonenemies[i].render(window, sprite_longenemy);
		if (!(checkOutOfBound(shotenemies[i])))
			shotenemies[i].render(window, sprite_shotenemy);
		if (!(checkOutOfBound(gangenemies[i])))
			gangenemies[i].render(window, sprite_gangenemy);
		if (!(checkOutOfBound(thugenemies[i])))
			thugenemies[i].render(window, sprite_thugenemy);
		if (!(checkOutOfBound(unknownenemies[i])))
			unknownenemies[i].render(window, sprite_unknownenemy);
		if (!(checkOutOfBound(glitchyenemies[i])))
			glitchyenemies[i].render(window, sprite_glitchyenemy);
		if (!(checkOutOfBound(advancedenemies[i])))
			advancedenemies[i].render(window, sprite_advancedenemy);
		if (!(checkOutOfBound(lazzyenemies[i])))
			lazzyenemies[i].render(window, sprite_lazzyenemy);
	}
	//boss render
	if (!(checkOutOfBound(boss_devplane)))
		if (boss_devplane.mode == 4)
			boss_devplane.render(window, sprite_devplane_ready);
		else
			boss_devplane.render(window, sprite_devplane);
	if (!(checkOutOfBound(boss_modifier)))
		boss_modifier.render(window, sprite_modifier);
	if (!(checkOutOfBound(boss_firethrower)))
		boss_firethrower.render(window, sprite_firethrower);
	if (!(checkOutOfBound(boss_alien)))
		boss_alien.render(window, sprite_alien);
	if (!(checkOutOfBound(boss_labplane)))
		boss_labplane.render(window, sprite_labplane);
	if (!(checkOutOfBound(boss_final)))
		boss_final.render(window, sprite_final);
}

void EnemySet::renderHitBox(sf::RenderWindow& window)
{
	//enemies hitbox render
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		if (!(checkOutOfBound(denemies[i])))
		{
			hb_denemy.rec.setPosition(sf::Vector2f(denemies[i].position.x + hb_denemy.hitbox_tl.x, denemies[i].position.y + hb_denemy.hitbox_tl.y));
			window.draw(hb_denemy.rec);
		}
		if (!(checkOutOfBound(douenemies[i])))
		{
			hb_douenemy.rec.setPosition(sf::Vector2f(douenemies[i].position.x + hb_douenemy.hitbox_tl.x, douenemies[i].position.y + hb_douenemy.hitbox_tl.y));
			window.draw(hb_douenemy.rec);
		}
		if (!(checkOutOfBound(lonenemies[i])))
		{
			hb_longenemy.rec.setPosition(sf::Vector2f(lonenemies[i].position.x + hb_longenemy.hitbox_tl.x, lonenemies[i].position.y + hb_longenemy.hitbox_tl.y));
			window.draw(hb_longenemy.rec);
		}
		if (!(checkOutOfBound(shotenemies[i])))
		{
			hb_shotenemy.rec.setPosition(sf::Vector2f(shotenemies[i].position.x + hb_shotenemy.hitbox_tl.x, shotenemies[i].position.y + hb_shotenemy.hitbox_tl.y));
			window.draw(hb_shotenemy.rec);
		}
		if (!(checkOutOfBound(gangenemies[i])))
		{
			hb_gangenemy.rec.setPosition(sf::Vector2f(gangenemies[i].position.x + hb_gangenemy.hitbox_tl.x, gangenemies[i].position.y + hb_gangenemy.hitbox_tl.y));
			window.draw(hb_gangenemy.rec);
		}
		if (!(checkOutOfBound(thugenemies[i])))
		{
			hb_thugenemy.rec.setPosition(sf::Vector2f(thugenemies[i].position.x + hb_thugenemy.hitbox_tl.x, thugenemies[i].position.y + hb_thugenemy.hitbox_tl.y));
			window.draw(hb_thugenemy.rec);
		}
		if (!(checkOutOfBound(unknownenemies[i])))
		{
			hb_unknownenemy.rec.setPosition(sf::Vector2f(unknownenemies[i].position.x + hb_unknownenemy.hitbox_tl.x, unknownenemies[i].position.y + hb_unknownenemy.hitbox_tl.y));
			window.draw(hb_unknownenemy.rec);
		}
		if (!(checkOutOfBound(glitchyenemies[i])))
		{
			hb_glitchyenemy.rec.setPosition(sf::Vector2f(glitchyenemies[i].position.x + hb_glitchyenemy.hitbox_tl.x, glitchyenemies[i].position.y + hb_glitchyenemy.hitbox_tl.y));
			window.draw(hb_glitchyenemy.rec);
		}
		if (!(checkOutOfBound(advancedenemies[i])))
		{
			hb_advancedenemy.rec.setPosition(sf::Vector2f(advancedenemies[i].position.x + hb_advancedenemy.hitbox_tl.x, advancedenemies[i].position.y + hb_advancedenemy.hitbox_tl.y));
			window.draw(hb_advancedenemy.rec);
		}
		if (!(checkOutOfBound(lazzyenemies[i])))
		{
			hb_lazzyenemy.rec.setPosition(sf::Vector2f(lazzyenemies[i].position.x + hb_lazzyenemy.hitbox_tl.x, lazzyenemies[i].position.y + hb_lazzyenemy.hitbox_tl.y));
			window.draw(hb_lazzyenemy.rec);
		}
	}
	//boss hitbox render
	if (!(checkOutOfBound(boss_devplane)))
	{
		hb_boss_devplane.rec.setPosition(boss_devplane.position + hb_boss_devplane.hitbox_tl);
		window.draw(hb_boss_devplane.rec);
	}
	if (!(checkOutOfBound(boss_modifier)))
	{
		hb_boss_modifier.rec.setPosition(boss_modifier.position + hb_boss_modifier.hitbox_tl);
		window.draw(hb_boss_modifier.rec);
	}
	if (!(checkOutOfBound(boss_firethrower)))
	{
		hb_boss_firethrower.rec.setPosition(boss_firethrower.position + hb_boss_firethrower.hitbox_tl);
		window.draw(hb_boss_firethrower.rec);
	}
	if (!(checkOutOfBound(boss_alien)))
	{
		hb_boss_alien.rec.setPosition(boss_alien.position + hb_boss_alien.hitbox_tl);
		window.draw(hb_boss_alien.rec);
	}
	if (!(checkOutOfBound(boss_labplane)))
	{
		hb_boss_labplane.rec.setPosition(boss_labplane.position + hb_boss_labplane.hitbox_tl);
		window.draw(hb_boss_labplane.rec);
	}
	if (!(checkOutOfBound(boss_final)))
	{
		hb_boss_final.rec.setPosition(boss_final.position + hb_boss_final.hitbox_tl);
		window.draw(hb_boss_final.rec);
	}
}

void EnemySet::spawn(int type, int x_position)
{
	switch(type)
	{
	case 1:
		if (avaliableEnemy(type) != -1)
		{
			denemies[avaliableEnemy(type)].shoot_count = 0;
			denemies[avaliableEnemy(type)].velocity.y = denemies[0].speed;
			denemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 2:
		if (avaliableEnemy(type) != -1)
		{
			douenemies[avaliableEnemy(type)].shoot_count = 0;
			douenemies[avaliableEnemy(type)].velocity.y = douenemies[0].speed;
			douenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 3:
		if (avaliableEnemy(type) != -1)
		{
			lonenemies[avaliableEnemy(type)].shoot_count = 0;
			lonenemies[avaliableEnemy(type)].velocity.y = lonenemies[0].speed;
			lonenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 4:
		if (avaliableEnemy(type) != -1)
		{
			shotenemies[avaliableEnemy(type)].shoot_count = 0;
			shotenemies[avaliableEnemy(type)].velocity.y = shotenemies[0].speed;
			shotenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 5:
		if (avaliableEnemy(type) != -1)
		{
			gangenemies[avaliableEnemy(type)].shoot_count = 0;
			gangenemies[avaliableEnemy(type)].velocity.y = gangenemies[0].speed;
			gangenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 6:
		if (avaliableEnemy(type) != -1)
		{
			thugenemies[avaliableEnemy(type)].shoot_count = 0;
			thugenemies[avaliableEnemy(type)].velocity.y = thugenemies[0].speed;
			thugenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 7:
		if (avaliableEnemy(type) != -1)
		{
			unknownenemies[avaliableEnemy(type)].shoot_count = 0;
			unknownenemies[avaliableEnemy(type)].velocity.y = unknownenemies[0].speed;
			unknownenemies[avaliableEnemy(type)].current_shoot_rate = 1000;
			unknownenemies[avaliableEnemy(type)].special_bullet_count = 0;
			unknownenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 8:
		if (avaliableEnemy(type) != -1)
		{
			glitchyenemies[avaliableEnemy(type)].shoot_count = 0;
			if (rand() % 2 == 1)
			{
				glitchyenemies[avaliableEnemy(type)].velocity.x = glitchyenemies[0].speed;
				glitchyenemies[avaliableEnemy(type)].position = sf::Vector2f(-80, x_position * 1.2f);
			}
			else
			{
				glitchyenemies[avaliableEnemy(type)].velocity.x = -glitchyenemies[0].speed;
				glitchyenemies[avaliableEnemy(type)].position = sf::Vector2f(SCREEN_WIDTH + 80, x_position * 1.2f);
			}
		}
		break;
	case 9:
		if (avaliableEnemy(type) != -1)
		{
			advancedenemies[avaliableEnemy(type)].shoot_count = 0;
			advancedenemies[avaliableEnemy(type)].velocity.y = advancedenemies[0].speed;
			advancedenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	case 10:
		if (avaliableEnemy(type) != -1)
		{
			lazzyenemies[avaliableEnemy(type)].shoot_count = 0;
			lazzyenemies[avaliableEnemy(type)].velocity.y = lazzyenemies[0].speed;
			lazzyenemies[avaliableEnemy(type)].current_shoot_rate = rand() % 600 + 200;
			lazzyenemies[avaliableEnemy(type)].position = sf::Vector2f(x_position, -80);
		}
		break;
	}
}

void EnemySet::spawn(int type)
{
	switch (type)
	{
	case 1:
		boss_devplane.initSetup();
		current_boss = 1;
		break;
	case 2:
		boss_modifier.initSetup();
		current_boss = 2;
		break;
	case 3:
		boss_firethrower.initSetup();
		current_boss = 3;
		break;
	case 4:
		boss_alien.initSetup();
		current_boss = 4;
		break;
	case 5:
		boss_labplane.initSetup();
		current_boss = 5;
		break;
		//case 6:
		//boss_final.initSetup();
		//current_boss = 6;
		//break;
	}
}

void EnemySet::initEnemy()
{
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		denemies[i].position.x = 0;
		denemies[i].position.y = 100000;
		douenemies[i].position.x = 0;
		douenemies[i].position.y = 100000;
		lonenemies[i].position.x = 0;
		lonenemies[i].position.y = 100000;
		shotenemies[i].position.x = 0;
		shotenemies[i].position.y = 100000;
		gangenemies[i].position.x = 0;
		gangenemies[i].position.y = 100000;
		thugenemies[i].position.x = 0;
		thugenemies[i].position.y = 100000;
		unknownenemies[i].position.x = 0;
		unknownenemies[i].position.y = 100000;
		glitchyenemies[i].position.x = 0;
		glitchyenemies[i].position.y = 100000;
		advancedenemies[i].position.x = 0;
		advancedenemies[i].position.y = 100000;
		lazzyenemies[i].position.x = 0;
		lazzyenemies[i].position.y = 100000;
	}
	//boss init
	boss_devplane.position.x = 0;
	boss_devplane.position.y = 100000;
	boss_devplane.mode = 0;
	boss_modifier.position.x = 0;
	boss_modifier.position.y = 100000;
	boss_modifier.mode = 0;
	boss_firethrower.position.x = 0;
	boss_firethrower.position.y = 100000;
	boss_firethrower.mode = 0;
	boss_alien.position.x = 0;
	boss_alien.position.y = 100000;
	boss_alien.mode = 0;
	boss_labplane.position.x = 0;
	boss_labplane.position.y = 100000;
	boss_labplane.mode = 0;
	boss_final.position.x = 0;
	boss_final.position.y = 100000;
	boss_final.mode = 0;

	current_boss = 0;
}

bool EnemySet::checkOutOfBound(Enemy& e)
{
	if (e.position.x < -300) return true;
	if (e.position.x > SCREEN_WIDTH + 300) return true;
	if (e.position.y < -500) return true;
	if (e.position.y > SCREEN_HEIGHT + 300) return true;

	return false;
}

int EnemySet::avaliableEnemy(int type)
{
	switch(type)
	{
		case 1: 
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(denemies[i]))
					return i;
			return -1;
		case 2:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(douenemies[i]))
					return i;
			return -1;
		case 3:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(lonenemies[i]))
					return i;
			return -1;
		case 4:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(shotenemies[i]))
					return i;
			return -1;
		case 5:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(gangenemies[i]))
					return i;
			return -1;
		case 6:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(thugenemies[i]))
					return i;
			return -1;
		case 7:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(unknownenemies[i]))
					return i;
			return -1;
		case 8:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(glitchyenemies[i]))
					return i;
			return -1;
		case 9:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(advancedenemies[i]))
					return i;
			return -1;
		case 10:
			for (int i = 0; i < MAX_DENEMY; i++)
				if (checkOutOfBound(lazzyenemies[i]))
					return i;
			return -1;
	}
	return -1;
}

void EnemySet::pushBack(sf::Time delta_time)
{
	for (int i = 0; i < MAX_DENEMY; i++)
	{
		if (!checkOutOfBound(denemies[i]))
		{
			if (denemies[i].position.x + hb_denemy.hitbox_tl.x + hb_denemy.hitbox_br.x > SCREEN_WIDTH)
				denemies[i].position.x = SCREEN_WIDTH - denemies[i].speed * delta_time.asSeconds() - hb_denemy.hitbox_tl.x - hb_denemy.hitbox_br.x;
			else if (denemies[i].position.x < 0)
				denemies[i].position.x = denemies[i].speed  * delta_time.asSeconds();
		}

		if (!checkOutOfBound(douenemies[i]))
		{
			if (douenemies[i].position.x + hb_douenemy.hitbox_tl.x + hb_douenemy.hitbox_br.x > SCREEN_WIDTH)
				douenemies[i].position.x = SCREEN_WIDTH - douenemies[i].speed * delta_time.asSeconds() - hb_douenemy.hitbox_tl.x - hb_douenemy.hitbox_br.x;
			else if (douenemies[i].position.x < 0)
				douenemies[i].position.x = douenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(lonenemies[i]))
		{
			if (lonenemies[i].position.x + hb_longenemy.hitbox_tl.x + hb_longenemy.hitbox_br.x > SCREEN_WIDTH)
				lonenemies[i].position.x = SCREEN_WIDTH - lonenemies[i].speed * delta_time.asSeconds() - hb_longenemy.hitbox_tl.x - hb_longenemy.hitbox_br.x;
			else if (lonenemies[i].position.x < 0)
				lonenemies[i].position.x = lonenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(shotenemies[i]))
		{
			if (shotenemies[i].position.x + hb_shotenemy.hitbox_tl.x + hb_shotenemy.hitbox_br.x > SCREEN_WIDTH)
				shotenemies[i].position.x = SCREEN_WIDTH - shotenemies[i].speed * delta_time.asSeconds() - hb_shotenemy.hitbox_tl.x - hb_shotenemy.hitbox_br.x;
			else if (shotenemies[i].position.x < 0)
				shotenemies[i].position.x = shotenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(gangenemies[i]))
		{
			if (gangenemies[i].position.x + hb_gangenemy.hitbox_tl.x + hb_gangenemy.hitbox_br.x > SCREEN_WIDTH)
				gangenemies[i].position.x = SCREEN_WIDTH - gangenemies[i].speed * delta_time.asSeconds() - hb_gangenemy.hitbox_tl.x - hb_gangenemy.hitbox_br.x;
			else if (gangenemies[i].position.x < 0)
				gangenemies[i].position.x = gangenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(thugenemies[i]))
		{
			if (thugenemies[i].position.x + hb_thugenemy.hitbox_tl.x + hb_thugenemy.hitbox_br.x > SCREEN_WIDTH)
				thugenemies[i].position.x = SCREEN_WIDTH - thugenemies[i].speed * delta_time.asSeconds() - hb_thugenemy.hitbox_tl.x - hb_thugenemy.hitbox_br.x;
			else if (thugenemies[i].position.x < 0)
				thugenemies[i].position.x = thugenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(unknownenemies[i]))
		{
			if (unknownenemies[i].position.x + hb_unknownenemy.hitbox_tl.x + hb_unknownenemy.hitbox_br.x > SCREEN_WIDTH)
				unknownenemies[i].position.x = SCREEN_WIDTH - unknownenemies[i].speed * delta_time.asSeconds() - hb_unknownenemy.hitbox_tl.x - hb_unknownenemy.hitbox_br.x;
			else if (unknownenemies[i].position.x < 0)
				unknownenemies[i].position.x = unknownenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(advancedenemies[i]))
		{
			if (advancedenemies[i].position.x + hb_advancedenemy.hitbox_tl.x + hb_advancedenemy.hitbox_br.x > SCREEN_WIDTH)
				advancedenemies[i].position.x = SCREEN_WIDTH - advancedenemies[i].speed * delta_time.asSeconds() - hb_advancedenemy.hitbox_tl.x - hb_advancedenemy.hitbox_br.x;
			else if (advancedenemies[i].position.x < 0)
				advancedenemies[i].position.x = advancedenemies[i].speed * delta_time.asSeconds();
		}

		if (!checkOutOfBound(lazzyenemies[i]))
		{
			if (lazzyenemies[i].position.x + hb_lazzyenemy.hitbox_tl.x + hb_lazzyenemy.hitbox_br.x > SCREEN_WIDTH)
				lazzyenemies[i].position.x = SCREEN_WIDTH - lazzyenemies[i].speed * delta_time.asSeconds() - hb_lazzyenemy.hitbox_tl.x - hb_lazzyenemy.hitbox_br.x;
			else if (lazzyenemies[i].position.x < 0)
				lazzyenemies[i].position.x = lazzyenemies[i].speed * delta_time.asSeconds();
		}
	}

	//boss movement
	//devplane
	if (boss_devplane.mode <= 3)
	{
		if (boss_devplane.position.x + hb_boss_devplane.hitbox_tl.x + hb_boss_devplane.hitbox_br.x > SCREEN_WIDTH - 20)
		{
			boss_devplane.position.x = SCREEN_WIDTH - 20 - boss_devplane.speed * delta_time.asSeconds() - hb_boss_devplane.hitbox_tl.x - hb_boss_devplane.hitbox_br.x;
			boss_devplane.velocity.x = -boss_devplane.speed;
		}
		else if (boss_devplane.position.x < 20)
		{
			boss_devplane.position.x = 20 + boss_devplane.speed * delta_time.asSeconds();
			boss_devplane.velocity.x = boss_devplane.speed;
		}
	}
	//modifier
	if (boss_modifier.mode == 2 || boss_modifier.mode == 3)
	{
		if (boss_modifier.position.x < 40)
		{
			boss_modifier.position.x = 40;
			boss_modifier.velocity.x = 0;
			boss_modifier.velocity.y = boss_modifier.speed;
		}
		else if (boss_modifier.position.y > 300)
		{
			boss_modifier.position.y = 300;
			boss_modifier.velocity.y = 0;
			boss_modifier.velocity.x = boss_modifier.speed;
		}
		else if (boss_modifier.position.x + hb_boss_modifier.hitbox_tl.x + hb_boss_modifier.hitbox_br.x > SCREEN_WIDTH - 40)
		{
			boss_modifier.position.x = SCREEN_WIDTH - 40 - hb_boss_modifier.hitbox_tl.x - hb_boss_modifier.hitbox_br.x;
			boss_modifier.velocity.x = 0;
			boss_modifier.velocity.y = -boss_modifier.speed;
		}
		else if (boss_modifier.position.y < boss_modifier.y_target)
		{
			boss_modifier.position.y = boss_modifier.y_target;
			boss_modifier.velocity.y = 0;
			boss_modifier.velocity.x = -boss_modifier.speed;
		}
	}
	else if (boss_modifier.mode == 5)
	{
		if (boss_modifier.position.x + hb_boss_modifier.hitbox_tl.x + hb_boss_modifier.hitbox_br.x > SCREEN_WIDTH - 40)
		{
			boss_modifier.position.x = SCREEN_WIDTH - 40 - boss_modifier.speed * delta_time.asSeconds() - hb_boss_modifier.hitbox_tl.x - hb_boss_modifier.hitbox_br.x;
			boss_modifier.velocity.x = -boss_modifier.speed * 2;
		}
		else if (boss_modifier.position.x < 40)
		{
			boss_modifier.position.x = 40 + boss_modifier.speed * delta_time.asSeconds();
			boss_modifier.velocity.x = boss_modifier.speed * 2;
		}
	}
	//firethrower
	if (boss_firethrower.mode <= 3)
	{
		if (boss_firethrower.position.x + hb_boss_firethrower.hitbox_tl.x + hb_boss_firethrower.hitbox_br.x > SCREEN_WIDTH - 20)
		{
			boss_firethrower.position.x = SCREEN_WIDTH - 20 - boss_firethrower.speed * delta_time.asSeconds() - hb_boss_firethrower.hitbox_tl.x - hb_boss_firethrower.hitbox_br.x;
			boss_firethrower.velocity.x = -boss_firethrower.speed;
		}
		else if (boss_firethrower.position.x < 20)
		{
			boss_firethrower.position.x = 20 + boss_firethrower.speed * delta_time.asSeconds();
			boss_firethrower.velocity.x = boss_firethrower.speed;
		}
	}
	//ailenShip
	if (boss_alien.mode <= 3)
	{
		if (boss_alien.position.x + hb_boss_alien.hitbox_tl.x + hb_boss_alien.hitbox_br.x > SCREEN_WIDTH - 20)
		{
			boss_alien.position.x = SCREEN_WIDTH - 20 - boss_alien.speed * delta_time.asSeconds() - hb_boss_alien.hitbox_tl.x - hb_boss_alien.hitbox_br.x;
			boss_alien.velocity.x = -boss_alien.speed;
		}
		else if (boss_alien.position.x < 20)
		{
			boss_alien.position.x = 20 + boss_alien.speed * delta_time.asSeconds();
			boss_alien.velocity.x = boss_alien.speed;
		}
	}
	//labplane
	if (boss_labplane.mode <= 3)
	{
		if (boss_labplane.position.x + hb_boss_labplane.hitbox_tl.x + hb_boss_labplane.hitbox_br.x > SCREEN_WIDTH - 20)
		{
			boss_labplane.position.x = SCREEN_WIDTH - 20 - boss_labplane.speed * delta_time.asSeconds() - hb_boss_labplane.hitbox_tl.x - hb_boss_labplane.hitbox_br.x;
			boss_labplane.velocity.x = -boss_labplane.speed;
		}
		else if (boss_labplane.position.x < 20)
		{
			boss_labplane.position.x = 20 + boss_labplane.speed * delta_time.asSeconds();
			boss_labplane.velocity.x = boss_labplane.speed;
		}
	}
	//final boss
	if (boss_final.mode <= 3)
	{
		if (boss_final.position.x + hb_boss_final.hitbox_tl.x + hb_boss_final.hitbox_br.x > SCREEN_WIDTH - 20)
		{
			boss_final.position.x = SCREEN_WIDTH - 20 - boss_final.speed * delta_time.asSeconds() - hb_boss_final.hitbox_tl.x - hb_boss_final.hitbox_br.x;
			boss_final.velocity.x = -boss_final.speed;
		}
		else if (boss_final.position.x < 20)
		{
			boss_final.position.x = 20 + boss_final.speed * delta_time.asSeconds();
			boss_final.velocity.x = boss_final.speed;
		}
	}
}