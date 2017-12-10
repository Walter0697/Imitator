#pragma once

#include "boss.hpp"

class AlienShip : public Boss
{

public:
	AlienShip();									//constructor
	~AlienShip();									//destructor

	sf::Vector2f four_shoot;						//four shooting position
	sf::Vector2f five_shoot;						//should be hard coded because that should follow the picture coordinate
	sf::Vector2f six_shoot;
	sf::Vector2f center_shoot;

	void initSetup();								//setup for the boss
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update

	int chance;										//chance for the boss to change mode
};