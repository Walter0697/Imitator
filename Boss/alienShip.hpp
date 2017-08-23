#pragma once

#include "boss.hpp"

class AlienShip : public Boss
{

public:
	AlienShip();
	~AlienShip();

	sf::Vector2f four_shoot;
	sf::Vector2f five_shoot;
	sf::Vector2f six_shoot;
	sf::Vector2f center_shoot;

	void initSetup();
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	int chance;
};