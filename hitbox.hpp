#pragma once

#include <SFML\Graphics.hpp>

class Hitbox
{

public:
	Hitbox();					//constructor
	~Hitbox();					//destructor

	sf::Vector2f hitbox_tl;		//top left position
	sf::Vector2f hitbox_br;		//bottom right position
	float hitbox_r;				//hitbox radius

	sf::RectangleShape rec;		//hitbox shape
	sf::CircleShape cir;

	void generateHitboxRec();	//generate a rectangle one if it is rectangle
	void generateHitboxCir();	//generate a circle one if it is cirle
};