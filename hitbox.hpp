#pragma once

#include <SFML\Graphics.hpp>

class Hitbox
{

public:
	Hitbox();
	~Hitbox();

	sf::Vector2f hitbox_tl;
	sf::Vector2f hitbox_br;
	float hitbox_r;

	sf::RectangleShape rec;
	sf::CircleShape cir;

	void generateHitboxRec();
	void generateHitboxCir();
};