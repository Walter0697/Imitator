#pragma once

#include "boss.hpp"

class DevPlane : public Boss
{

public:
	DevPlane();
	~DevPlane();

	sf::Vector2f four_shoot;

	void initSetup();
	void render(sf::RenderWindow&, sf::Sprite&);
	void update(sf::Time);

	int chance;
};