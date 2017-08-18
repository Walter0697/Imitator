#include "hud.hpp"

Hud::Hud(Player* player)
{
	this->player = player;	
}

Hud::~Hud() {}


void Hud::setup()
{
	healthBar.setPosition(0, SCREEN_HEIGHT - healthSize.y);
	health.setPosition(0, SCREEN_HEIGHT - healthSize.y / 2);
	shield.setPosition(0, SCREEN_HEIGHT - healthSize.y);

	text.setFont(font);
	text.setString(std::to_string(player->score));
	text.setCharacterSize(30);
	text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2, SCREEN_HEIGHT - text.getLocalBounds().height * 1.5);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Style::Default);
}

void Hud::render(sf::RenderWindow& window)
{
	//score
	text.setString(std::to_string(player->score));
	text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2, SCREEN_HEIGHT - text.getLocalBounds().height * 1.5);
	window.draw(text);
		
	//health bar
	this->health.setTextureRect(sf::IntRect(0, 0, player->hp * healthSize.x / player->maxhp , healthSize.y / 2));
	this->shield.setTextureRect(sf::IntRect(0, 0, player->shield * healthSize.x / player->maxshield , healthSize.y / 2));
	window.draw(healthBar);
	window.draw(health);
	window.draw(shield);

	//status type
	int current_position = SCREEN_HEIGHT - 100;
	if (player->onFire > 0)
	{
		status_sprite[0].setPosition(SCREEN_WIDTH - 30, current_position);
		current_position -= 40;
		window.draw(status_sprite[0]);
	}

	//bullet type
	for (int i = 0; i < player->CURRENT_HOLD_BULLET; i++)
	{
		if (player->shoot_type[i] != 0)
		{
			bullet_sprite[player->shoot_type[i] - 1].setPosition(SCREEN_WIDTH - 60 - (i * 40), SCREEN_HEIGHT - 60 - (i * 8));
			window.draw(bullet_sprite[player->shoot_type[i] - 1]);
		}
	}
}