#pragma once

#include "../renderable.hpp"

#include "../player.hpp"

class RadShield : public Renderable
{

public:
	Player* player;
	RadShield(Player* player);
	~RadShield();

	int health;
	Hitbox hitbox;
	sf::CircleShape ShieldSprite;

	void addShield(int);
	void render(sf::RenderWindow&);
	void renderHitBox(sf::RenderWindow&);
};