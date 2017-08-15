#include "shotgun.hpp"

ShotGun::ShotGun()
{
	//setting of the shot gun
	velocity.x = 0;
	velocity.y = 0;
	damage = 8;
	speed = 700;
	shoot_rate = 1500;
	lifespan = 0;
}

ShotGun::~ShotGun() {}

void ShotGun::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void ShotGun::update(sf::Time delta_time)
{
	lifespan -= delta_time.asSeconds();
	if (velocity.x > speed * delta_time.asSeconds()) velocity.x -= speed * delta_time.asSeconds();
	else if (velocity.x < -speed * delta_time.asSeconds()) velocity.x += speed * delta_time.asSeconds();
	else velocity.x = 0;

	velocity.y -= speed * delta_time.asSeconds();
	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();

	if (lifespan <= 0)
	{
		lifespan = 0;
		position = sf::Vector2f(-800, 0);
		velocity = sf::Vector2f(0, 0);
	}
}