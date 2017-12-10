#pragma once

#include "boss.hpp"

class LabPlane : public Boss
{

public:
	LabPlane();										//constructor
	~LabPlane();									//destructor

	sf::Vector2f four_shoot;						//shooting position
	sf::Vector2f five_shoot;

	void initSetup();								//initialize set up
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update

	int chance;										//chance to change mode
};