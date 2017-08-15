#pragma once

#include "../renderable.hpp"

#include "../defs.h"

class Story : public Renderable
{

public:

	Story();
	~Story();

	void setup();
	void render(sf::RenderWindow&);

	sf::Sprite healthBar;
	sf::Vector2u healthSize;
	sf::Sprite health;
};