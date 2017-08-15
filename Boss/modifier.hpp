#pragma once

#include "boss.hpp"

class Modifier : public Boss
{

public:
	Modifier();
	~Modifier();

	sf::Vector2f four_shoot;
	sf::Vector2f five_shoot;

	void initSetup();
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	int chance;
};