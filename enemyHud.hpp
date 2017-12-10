#pragma once

#include "renderable.hpp"

#include "enemyset.hpp"

#include "defs.h"

class EnemyHud : public Renderable
{

public:
	//this is the enemyhud to render the boss health
	EnemySet* enemySet;							//a pointer to the enemyset
	EnemyHud(EnemySet* enemySet);				//constructor
	~EnemyHud();								//destructor

	void setup();								//set up 
	void render(sf::RenderWindow&);				//render

	sf::Sprite healthBar;						//health bar sprite
	sf::Vector2u healthSize;					//health bar size
	sf::Sprite health;							//health sprite that will resize according to the health

	sf::Font font;								//font and text
	sf::Text text;

private:
	float getHealth();							//get health from the enemy class
	float getMaxHealth();						//get max health from the enemy class

};