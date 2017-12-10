#pragma once

#include "boss.hpp"

class DevPlane : public Boss
{

public:
	DevPlane();										//constructor
	~DevPlane();									//destructor

	sf::Vector2f four_shoot;						//setting the shooting position

	void initSetup();								//initial set up
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update

	int chance;										//chance to change the mode
};