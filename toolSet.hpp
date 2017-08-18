#pragma once

#include "renderable.hpp"
#include "updateable.hpp"

#include "Tools/GreenShield.hpp"
#include "Tools/BlueShield.hpp"
#include "Tools/YellowShield.hpp"
#include "Tools/healthPack.hpp"
#include "Tools/imumium.hpp"
#include "Enemy/enemy.hpp"

#include "hitbox.hpp"

#include "defs.h"

class ToolSet : public Renderable, public Updateable
{
public:
	ToolSet();
	~ToolSet();

	void render(sf::RenderWindow&);
	void renderHitBox(sf::RenderWindow&);
	void update(sf::Time);

	void initTool();
	bool checkOutOfBound(Tool&);
	int availableTool(int);

	void drop(Enemy&, int);

	GreenShield shieldTool[MAX_GREEN_SHIELD];
	BlueShield bshieldTool[MAX_BLUE_SHIELD];
	YellowShield yshieldTool[MAX_YELLOW_SHIELD];
	HealthPack healthpack[MAX_HEALTH_PACK];
	Imumium imumium[MAX_IMUMIUM];

	Hitbox hb_greenShield;
	Hitbox hb_blueShield;
	Hitbox hb_yellowShield;
	Hitbox hb_healthPack;
	Hitbox hb_imumium;

	sf::Sprite sprite_greenShield;
	sf::Sprite sprite_blueShield;
	sf::Sprite sprite_yellowShield;
	sf::Sprite sprite_healthPack;
	sf::Sprite sprite_imumium;
};