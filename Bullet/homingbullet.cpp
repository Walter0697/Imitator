#include "homingbullet.hpp"

HomingBullet::HomingBullet()
{
	//setting of the homing bullet
	velocity.x = 0;
	velocity.y = 0;
	damage = 20;
	speed = 200 ;
	shoot_rate = 10;
	turning_speed = 3;
	target = sf::Vector2f(-1, -1);
	target_countdown = 0;
}

HomingBullet::~HomingBullet() {} 

void HomingBullet::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	sprite.setPosition(position);
	window.draw(sprite);
}


void HomingBullet::update(sf::Time delta_time)
{
	target_countdown -= delta_time.asMilliseconds();

	if (target.x != -1 && pow(target.x - position.x, 2) + pow(target.y - position.y, 2) > 500)
	{ 
		dot = velocity.x * -(target.y - position.y) + velocity.y * (target.x - position.x);

		if (dot > 0)
			angle -= turning_speed * delta_time.asSeconds();
		else
			angle += turning_speed * delta_time.asSeconds();

		velocity.x = speed * cos(angle);
		velocity.y = speed * sin(angle);
	}
	

	position.x += velocity.x * delta_time.asSeconds();
	position.y += velocity.y * delta_time.asSeconds();
}

void HomingBullet::setTarget(sf::Vector2f& target)
{
	this->target = target;
}