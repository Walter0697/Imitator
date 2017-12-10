#pragma once

#include "enemy.hpp"

//advanced ship enemy
class Advanced : public Enemy
{

public:
	Advanced();										//Constructor
	~Advanced();									//Destructor

	void render(sf::RenderWindow&, sf::Sprite&);	//rendering
	void update(sf::Time);							//updating
};