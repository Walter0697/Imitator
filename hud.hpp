#pragma once

#include "renderable.hpp"

#include "player.hpp"
#include "enemyset.hpp"

#include "defs.h"

class Hud : public Renderable
{

public:

	Player* player;									//pointer to the player and enemy
	EnemySet* enemySet;
	Hud(Player* player, EnemySet* enemySet);		//constructor
	~Hud();											//destructor

	void setup();									//set up for the hud
	void render(sf::RenderWindow&);					//render

	sf::Sprite healthBar;							//sprite for the health bar
	sf::Vector2u healthSize;						//size of the health bar
	sf::Sprite health;								//sprite that will resize according to the health
	sf::Sprite shield;								//current shield

	sf::Font font;									//text and font
	sf::Text text;

	//bullet type
	sf::Sprite bullet_sprite[NUM_OF_BULLET];
	//status type
	sf::Sprite status_sprite[NUM_OF_STATUS];
};