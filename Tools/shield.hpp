#pragma once

#include "../renderable.hpp"

#include "../player.hpp"

class Shield : public Renderable
{

public:
	Player* player;
	Shield(Player* player);
	~Shield();

	int level;
	Hitbox hitbox;
	sf::CircleShape ShieldSprite;

	void addShield(int);
	void render(sf::RenderWindow&);
	void renderHitBox(sf::RenderWindow&);
};