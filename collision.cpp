#include "collision.hpp"

Collision::Collision() {}

Collision::~Collision() {}

bool Collision::RectangleCircleCollision(sf::Vector2f rec_tl, sf::Vector2f rec_br, sf::Vector2f cir_center, float cir_radius) 
{
	if (cir_center.x + cir_radius < rec_tl.x) return false;
	if (cir_center.x - cir_radius > rec_br.x) return false;
	if (cir_center.y + cir_radius < rec_tl.y) return false;
	if (cir_center.y - cir_radius > rec_br.y) return false;
	return true;
}

bool Collision::RectangleRectangleCollision(sf::Vector2f a_tl, sf::Vector2f a_br, sf::Vector2f b_tl, sf::Vector2f b_br) 
{ 
	if (a_br.x < b_tl.x) return false;
	if (a_tl.x > b_br.x) return false;
	if (a_br.y < b_tl.y) return false;
	if (a_tl.y > b_br.y) return false;
	return true;
}

bool Collision::CircleCircleCollision(sf::Vector2f a_center, float a_radius, sf::Vector2f b_center, float b_radius) 
{ 
	return pow(a_radius + b_radius, 2) >= (pow(a_center.x - b_center.x, 2) + pow(a_center.y - b_center.y, 2));
}

bool Collision::ShieldBulletCollision(Player* p, float radius, Bullet& b, Hitbox& b_hb)
{
	if (b_hb.hitbox_r != 0.f)
		return CircleCircleCollision(p->position, radius, b.position, b_hb.hitbox_r);
	else
		return RectangleCircleCollision(b.position + b_hb.hitbox_tl, b.position + b_hb.hitbox_br, p->position, radius);
}

bool Collision::EnemyBulletCollision(Enemy& e, Hitbox& e_hb, Bullet& b, Hitbox& b_hb)
{
	if (b_hb.hitbox_r != 0.f)
		if (e_hb.hitbox_r != 0.f)
			return CircleCircleCollision(e.position, e_hb.hitbox_r, b.position, b_hb.hitbox_r);
		else
			return RectangleCircleCollision(e.position + e_hb.hitbox_tl, e.position + e_hb.hitbox_br, b.position, b_hb.hitbox_r);
	else
		if (e_hb.hitbox_r != 0.f)
			return RectangleCircleCollision(b.position + b_hb.hitbox_tl, b.position + b_hb.hitbox_br, e.position, e_hb.hitbox_r);
		else
			return RectangleRectangleCollision(e.position + e_hb.hitbox_tl, e.position + e_hb.hitbox_br, b.position + b_hb.hitbox_tl, b.position + b_hb.hitbox_br);
}

bool Collision::PlayerBulletCollision(Player* p, Bullet& b, Hitbox& b_hb)
{
	if (b_hb.hitbox_r != 0.f)
		return RectangleCircleCollision(p->position + p->hb.hitbox_tl, p->position + p->hb.hitbox_br, b.position, b_hb.hitbox_r);
	else
		return RectangleRectangleCollision(p->position + p->hb.hitbox_tl, p->position + p->hb.hitbox_br, b.position + b_hb.hitbox_tl, b.position + b_hb.hitbox_br);
}