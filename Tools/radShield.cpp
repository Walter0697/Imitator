#include "radShield.hpp"

RadShield::RadShield(Player* player)
{
	this->player = player;
	ShieldSprite.setPosition(player->position);
	ShieldSprite.setFillColor(sf::Color::Transparent);
	ShieldSprite.setOutlineColor(sf::Color::Yellow);
	ShieldSprite.setOutlineThickness(5);

	this->health = 0;
}

RadShield::~RadShield() {}

void RadShield::addShield(int num)
{
	this->health += num;
	if (this->health > 0) hitbox.hitbox_r = 50 + this->health / 2;
	else
	{
		hitbox.hitbox_r = 0;
		this->health = 0;
	}
	hitbox.generateHitboxCir();
}

void RadShield::render(sf::RenderWindow& window)
{
	if (this->health != 0)
	{
		ShieldSprite.setPosition(player->position.x + player->size.x / 2, player->position.y + player->size.y / 2);
		hitbox.cir.setPosition(player->position.x + player->size.x / 2, player->position.y + player->size.y / 2);
		ShieldSprite.setRadius(50 + health / 2);
		ShieldSprite.setOrigin(50 + health / 2, 50 + health / 2);
		window.draw(ShieldSprite);
	}
}

void RadShield::renderHitBox(sf::RenderWindow& window)
{
	window.draw(hitbox.cir);
}