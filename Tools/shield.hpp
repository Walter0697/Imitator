#pragma once

#include "../renderable.hpp"

#include "../player.hpp"

class Shield : public Renderable
{

public:
	Player* player;									//pointer to the player
	Shield(Player* player);							//constructor
	~Shield();										//destructor

	int level;										//level of the shield
	Hitbox hitbox;									//hitbox of the shield
	sf::CircleShape ShieldSprite;					//sprite of the shield

	void addShield(int);							//adding shield
	void render(sf::RenderWindow&);					//render
	void renderHitBox(sf::RenderWindow&);			//render the hitbox of the shield
};