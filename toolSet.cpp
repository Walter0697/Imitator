#include "toolSet.hpp"

ToolSet::ToolSet() 
{
	this->hb_greenShield.hitbox_r = 11.f;
	this->hb_greenShield.generateHitboxCir();

	this->hb_blueShield.hitbox_r = 11.f;
	this->hb_blueShield.generateHitboxCir();

	this->hb_yellowShield.hitbox_r = 11.f;
	this->hb_yellowShield.generateHitboxCir();

	this->hb_healthPack.hitbox_r = 11.f;
	this->hb_healthPack.generateHitboxCir();

	this->hb_imumium.hitbox_r = 8.f;
	this->hb_imumium.generateHitboxCir();

	this->hb_stone.hitbox_r = 8.f;
	this->hb_stone.generateHitboxCir();

	this->hb_clock.hitbox_r = 8.f;
	this->hb_clock.generateHitboxCir();

	initTool();
}

ToolSet::~ToolSet() {}

void ToolSet::render(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_GREEN_SHIELD; i++)
		if (!checkOutOfBound(shieldTool[i]))
			shieldTool[i].render(window, sprite_greenShield);

	for (int i = 0; i < MAX_BLUE_SHIELD; i++)
		if (!checkOutOfBound(bshieldTool[i]))
			bshieldTool[i].render(window, sprite_blueShield);

	for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
		if (!checkOutOfBound(yshieldTool[i]))
			yshieldTool[i].render(window, sprite_yellowShield);

	for (int i = 0; i < MAX_HEALTH_PACK; i++)
		if (!checkOutOfBound(healthpack[i]))
			healthpack[i].render(window, sprite_healthPack);

	for (int i = 0; i < MAX_IMUMIUM; i++)
		if (!checkOutOfBound(imumium[i]))
			imumium[i].render(window, sprite_imumium);

	for (int i = 0; i < MAX_STONE; i++)
		if (!checkOutOfBound(stoneTool[i]))
			stoneTool[i].render(window, sprite_stone);

	for (int i = 0; i < MAX_CLOCK; i++)
		if (!checkOutOfBound(clocksTool[i]))
			clocksTool[i].render(window, sprite_clock);
} 

void ToolSet::renderHitBox(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_GREEN_SHIELD; i++)
	{
		if (!checkOutOfBound(shieldTool[i]))
		{
			hb_greenShield.cir.setPosition(shieldTool[i].position);
			window.draw(hb_greenShield.cir);
		}
	}
	for (int i = 0; i < MAX_BLUE_SHIELD; i++)
	{
		if (!checkOutOfBound(bshieldTool[i]))
		{
			hb_blueShield.cir.setPosition(bshieldTool[i].position);
			window.draw(hb_blueShield.cir);
		}
	}
	for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
	{
		if (!checkOutOfBound(yshieldTool[i]))
		{
			hb_yellowShield.cir.setPosition(yshieldTool[i].position);
			window.draw(hb_yellowShield.cir);
		}
	}
	for (int i = 0; i < MAX_HEALTH_PACK; i++)
	{
		if (!checkOutOfBound(healthpack[i]))
		{
			hb_healthPack.cir.setPosition(healthpack[i].position);
			window.draw(hb_healthPack.cir);
		}
	}
	for (int i = 0; i < MAX_IMUMIUM; i++)
	{
		if (!checkOutOfBound(imumium[i]))
		{
			hb_imumium.cir.setPosition(imumium[i].position);
			window.draw(hb_imumium.cir);
		}
	}
	for (int i = 0; i < MAX_STONE; i++)
	{
		if (!checkOutOfBound(stoneTool[i]))
		{
			hb_stone.cir.setPosition(stoneTool[i].position);
			window.draw(hb_stone.cir);
		}
	}
	for (int i = 0; i < MAX_CLOCK; i++)
	{
		if (!checkOutOfBound(clocksTool[i]))
		{
			hb_clock.cir.setPosition(clocksTool[i].position);
			window.draw(hb_clock.cir);
		}
	}
}

void ToolSet::update(sf::Time delta_time)
{
	for (int i = 0; i < MAX_GREEN_SHIELD; i++)
		shieldTool[i].update(delta_time);
	
	for (int i = 0; i < MAX_BLUE_SHIELD; i++)
		bshieldTool[i].update(delta_time);
	
	for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
		yshieldTool[i].update(delta_time);

	for (int i = 0; i < MAX_HEALTH_PACK; i++)
		healthpack[i].update(delta_time);

	for (int i = 0; i < MAX_IMUMIUM; i++)
		imumium[i].update(delta_time);

	for (int i = 0; i < MAX_STONE; i++)
		stoneTool[i].update(delta_time);

	for (int i = 0; i < MAX_CLOCK; i++)
		clocksTool[i].update(delta_time);
}

int ToolSet::availableTool(int type)
{
	switch (type)
	{
	case 1:
		for (int i = 0; i < MAX_GREEN_SHIELD; i++)
			if (checkOutOfBound(shieldTool[i]))
				return i;
		return 0;
	case 2:
		for (int i = 0; i < MAX_BLUE_SHIELD; i++)
			if (checkOutOfBound(bshieldTool[i]))
				return i;
		return 0;
	case 3:
		for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
			if (checkOutOfBound(yshieldTool[i]))
				return i;
		return 0;
	case 4:
		for (int i = 0; i < MAX_HEALTH_PACK; i++)
			if (checkOutOfBound(healthpack[i]))
				return i;
		return 0;
	case 5:
		for (int i = 0; i < MAX_IMUMIUM; i++)
			if (checkOutOfBound(imumium[i]))
				return i;
		return 0;
	case 6:
		for (int i = 0; i < MAX_STONE; i++)
			if (checkOutOfBound(stoneTool[i]))
				return i;
		return 0;
	case 7:
		for (int i = 0; i < MAX_CLOCK; i++)
			if (checkOutOfBound(clocksTool[i]))
				return i;
		return 0;
	}
	return 0;
}

void ToolSet::drop(Enemy& enemy, int type)
{
	switch (type)
	{
	case 1:
		shieldTool[availableTool(type)].velocity = sf::Vector2f(0, shieldTool[0].speed);
		shieldTool[availableTool(type)].position = enemy.position;
		break;
	case 2:
		bshieldTool[availableTool(type)].velocity = sf::Vector2f(0, bshieldTool[0].speed);
		bshieldTool[availableTool(type)].position = enemy.position;
		break;
	case 3:
		yshieldTool[availableTool(type)].velocity = sf::Vector2f(0, yshieldTool[0].speed);
		yshieldTool[availableTool(type)].position = enemy.position;
		break;
	case 4:
		healthpack[availableTool(type)].velocity = sf::Vector2f(0, healthpack[0].speed);
		healthpack[availableTool(type)].position = enemy.position;
		break;
	case 5:
		imumium[availableTool(type)].velocity = sf::Vector2f(0, imumium[0].speed);
		imumium[availableTool(type)].position = enemy.position;
		break;
	case 6:
		stoneTool[availableTool(type)].velocity = sf::Vector2f(0, stoneTool[0].speed);
		stoneTool[availableTool(type)].position = enemy.position;
		break;
	case 7:
		clocksTool[availableTool(type)].velocity = sf::Vector2f(0, clocksTool[0].speed);
		clocksTool[availableTool(type)].position = enemy.position;
		break;
	}
}

void ToolSet::initTool()
{
	for (int i = 0; i < MAX_GREEN_SHIELD; i++)
	{
		shieldTool[i].position = sf::Vector2f(0, -700);
		shieldTool[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_BLUE_SHIELD; i++)
	{
		bshieldTool[i].position = sf::Vector2f(0, -700);
		bshieldTool[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_YELLOW_SHIELD; i++)
	{
		yshieldTool[i].position = sf::Vector2f(0, -700);
		yshieldTool[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_HEALTH_PACK; i++)
	{
		healthpack[i].position = sf::Vector2f(0, -700);
		healthpack[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_IMUMIUM; i++)
	{
		imumium[i].position = sf::Vector2f(0, -700);
		imumium[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_STONE; i++)
	{
		stoneTool[i].position = sf::Vector2f(0, -700);
		stoneTool[i].velocity = sf::Vector2f(0, 0);
	}

	for (int i = 0; i < MAX_CLOCK; i++)
	{
		clocksTool[i].position = sf::Vector2f(0, -700);
		clocksTool[i].velocity = sf::Vector2f(0, 0);
	}
}

bool ToolSet::checkOutOfBound(Tool& tool)
{
	if (tool.position.x < -300) return true;
	if (tool.position.x > SCREEN_WIDTH + 300) return true;
	if (tool.position.y < -300) return true;
	if (tool.position.y > SCREEN_HEIGHT + 300) return true;
	return false;
}