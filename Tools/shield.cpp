#include "shield.hpp"

Shield::Shield(Player* player)
{
	this->player = player;
	ShieldSprite.setPosition(player->position);
	ShieldSprite.setFillColor(sf::Color::Transparent);
	ShieldSprite.setOutlineColor(sf::Color::Green);
	ShieldSprite.setOutlineThickness(5);

	this->level = 0;
}

Shield::~Shield() {}

void Shield::addShield(int num)
{
	this->level += num;
	if (this->level != 0) hitbox.hitbox_r = 45 + this->level * 20;
	else hitbox.hitbox_r = 0;
	hitbox.generateHitboxCir();
}

void Shield::render(sf::RenderWindow& window)
{
	ShieldSprite.setPosition(player->position.x + player->size.x / 2, player->position.y + player->size.y / 2);
	hitbox.cir.setPosition(player->position.x + player->size.x / 2, player->position.y + player->size.y / 2);
	for (int i = 0; i < level; i++)
	{
		ShieldSprite.setRadius(60 + i * 20);
		ShieldSprite.setOrigin(60 + i * 20, 60 + i * 20);
		window.draw(ShieldSprite);
	}
}

void Shield::renderHitBox(sf::RenderWindow& window)
{
	window.draw(hitbox.cir);
}