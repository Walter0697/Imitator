#pragma once

#include "boss.hpp"

class LabPlane : public Boss
{

public:
	LabPlane();
	~LabPlane();

	sf::Vector2f four_shoot;
	sf::Vector2f five_shoot;

	void initSetup();
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	int chance;
};