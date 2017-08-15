#include "hitbox.hpp"

Hitbox::Hitbox()
{
	//initialization
	hitbox_tl = sf::Vector2f(0, 0);
	hitbox_br = sf::Vector2f(0, 0);
	hitbox_r = 0.f;
}

Hitbox::~Hitbox() {}

void Hitbox::generateHitboxRec()
{
	rec.setSize(sf::Vector2f(hitbox_br.x - hitbox_tl.x, hitbox_br.y - hitbox_tl.y));
	rec.setFillColor(sf::Color(255, 0, 0, 80));
}

void Hitbox::generateHitboxCir()
{
	cir.setRadius(hitbox_r);
	cir.setOrigin(sf::Vector2f(hitbox_r, hitbox_r));
	cir.setFillColor(sf::Color(255, 0, 0, 80));
}