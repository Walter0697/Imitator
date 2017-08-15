#pragma once

#include "../updateable.hpp"

class Tool : public Updateable
{

public:
	Tool();
	~Tool();

	void render(sf::RenderWindow&, sf::Sprite&);     
	void update(sf::Time);

	float speed;
};