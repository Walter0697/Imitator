#pragma once

#include "boss.hpp"

class FinalBoss : public Boss
{

public:
	FinalBoss();									//constructor
	~FinalBoss();									//destructor

	sf::Vector2f four_shoot;						//shooting position
	sf::Vector2f five_shoot;

	void initSetup();								//initialize the setup
	void render(sf::RenderWindow&, sf::Sprite&);	//render
	void update(sf::Time);							//update

	int chance;										//chance to change mode
};