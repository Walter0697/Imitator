#pragma once

#include <SFML/Graphics.hpp>

class Renderable
{

public:

	virtual void render(sf::RenderWindow&) = 0;
};
