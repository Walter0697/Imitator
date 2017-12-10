#pragma once

#include "../updateable.hpp"

class Tool : public Updateable
{

public:
	Tool();											//constructor
	~Tool();										//destructor
	
	void render(sf::RenderWindow&, sf::Sprite&);    //render
	void update(sf::Time);							//update

	float speed;									//speed of the tool
};