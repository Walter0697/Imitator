#pragma once

#include "renderable.hpp"

#include "enemyset.hpp"

#include "defs.h"

class EnemyHud : public Renderable
{

public:
	EnemySet* enemySet;
	EnemyHud(EnemySet* enemySet);
	~EnemyHud();

	void setup();
	void render(sf::RenderWindow&);

	sf::Sprite healthBar;
	sf::Vector2u healthSize;
	sf::Sprite health;

	sf::Font font;
	sf::Text text;

private:
	float getHealth();
	float getMaxHealth();

};