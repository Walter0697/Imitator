#pragma once

#include "renderable.hpp"

#include "player.hpp"
#include "enemyset.hpp"

#include "defs.h"

class Hud : public Renderable
{

public:

	Player* player;
	EnemySet* enemySet;
	Hud(Player* player, EnemySet* enemySet);
	~Hud();

	void setup();
	void render(sf::RenderWindow&);

	sf::Sprite healthBar;
	sf::Vector2u healthSize;
	sf::Sprite health;
	sf::Sprite shield;

	sf::Font font;
	sf::Text text;

	//bullet type
	sf::Sprite bullet_sprite[NUM_OF_BULLET];
	//status type
	sf::Sprite status_sprite[NUM_OF_STATUS];
};