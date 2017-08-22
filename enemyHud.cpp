#include "enemyHud.hpp"

EnemyHud::EnemyHud(EnemySet* enemySet)
{
	this->enemySet = enemySet;
}

EnemyHud::~EnemyHud() {}

void EnemyHud::setup()
{
	healthBar.setPosition(0, -10);
	health.setPosition(0, -10);
}

void EnemyHud::render(sf::RenderWindow& window)
{
	if (enemySet->current_boss != 0)
	{
		health.setTextureRect(sf::IntRect(0, 0, getHealth() * healthSize.x / getMaxHealth(), healthSize.y));
		window.draw(healthBar);
		window.draw(health);
	}
}

float EnemyHud::getHealth()
{
	switch (enemySet->current_boss)
	{
	case 1:
		return enemySet->boss_devplane.hp;
	case 2:
		return enemySet->boss_modifier.hp;
	case 3:
		return enemySet->boss_firethrower.hp;
	}
	return 0;
}

float EnemyHud::getMaxHealth()
{
	switch (enemySet->current_boss)
	{
	case 1:
		return enemySet->boss_devplane.maxhp;
	case 2:
		return enemySet->boss_modifier.maxhp;
	case 3:
		return enemySet->boss_firethrower.maxhp;
	}
	return 0;
}