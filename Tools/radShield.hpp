#pragma once

#include "../renderable.hpp"

#include "../player.hpp"

class RadShield : public Renderable
{

public:
	Player* player;
	RadShield(Player* player);				//constructor
	~RadShield();							//destructor

	int health;								//health of the shield
	Hitbox hitbox;							//hitbox of the shield
	sf::CircleShape ShieldSprite;			//sprite for the shield

	void addShield(int);					//add shield
	void render(sf::RenderWindow&);			//render
	void renderHitBox(sf::RenderWindow&);	//render the hitbox
};