#pragma once

#include "renderable.hpp"

#include "player.hpp"

#include "defs.h"

class Hud : public Renderable
{

public:

	Player* player;
	Hud(Player* player);
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
	sf::Sprite bullet_sprite[12];
	//status type
	sf::Sprite status_sprite[3];
};