#pragma once

#include "renderable.hpp"
#include "updateable.hpp"

#include "Tools/GreenShield.hpp"
#include "Tools/BlueShield.hpp"
#include "Tools/YellowShield.hpp"
#include "Tools/healthPack.hpp"
#include "Tools/imumium.hpp"
#include "Tools/ausStone.hpp"
#include "Tools/clock.hpp"
#include "Enemy/enemy.hpp"

#include "hitbox.hpp"

#include "defs.h"

class ToolSet : public Renderable, public Updateable
{
public:
	ToolSet();									//constructor
	~ToolSet();									//destructor

	void render(sf::RenderWindow&);				//render all the tools
	void renderHitBox(sf::RenderWindow&);		//render all hitboxes of the tools
	void update(sf::Time);						//update

	void initTool();							//initialize tool
	bool checkOutOfBound(Tool&);				//check if the tool is avaliable to spawn
	int availableTool(int);						//find the tool to spawn

	void drop(Enemy&, int);						//drop by an enemy

	//array of the tools
	GreenShield shieldTool[MAX_GREEN_SHIELD];			
	BlueShield bshieldTool[MAX_BLUE_SHIELD];
	YellowShield yshieldTool[MAX_YELLOW_SHIELD];
	HealthPack healthpack[MAX_HEALTH_PACK];
	Imumium imumium[MAX_IMUMIUM];
	AusStone stoneTool[MAX_STONE];
	Clock clocksTool[MAX_CLOCK];

	//hitbox of the tools
	Hitbox hb_greenShield;
	Hitbox hb_blueShield;
	Hitbox hb_yellowShield;
	Hitbox hb_healthPack;
	Hitbox hb_imumium;
	Hitbox hb_stone;
	Hitbox hb_clock;

	//sprite of the tools
	sf::Sprite sprite_greenShield;
	sf::Sprite sprite_blueShield;
	sf::Sprite sprite_yellowShield;
	sf::Sprite sprite_healthPack;
	sf::Sprite sprite_imumium;
	sf::Sprite sprite_stone;
	sf::Sprite sprite_clock;
};