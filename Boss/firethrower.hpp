#pragma once

#include "boss.hpp"

class FireThrower : public Boss
{

public:
	FireThrower();											//constructor
	~FireThrower();											//destructor

	sf::Vector2f four_shoot;								//shooting position
	sf::Vector2f five_shoot;
	
	void initSetup();										//initialize set up
	void render(sf::RenderWindow&, sf::Sprite&);			//render
	void update(sf::Time);									//update

	int chance;												//chance to change mode
	int countdown;											//countdown to change mode
};