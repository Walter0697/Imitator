#include <iostream>

#include "manager.hpp"

Manager::Manager()
{ }

const sf::Texture & Manager::get_texture(std::string key, sf::Color mask)
{

	if (this->textures.count(key) == 0)
	{

		sf::Image image;
		image.loadFromFile(key);
		
		std::cout << key << " loaded from file." << std::endl;

		if (mask != sf::Color::Transparent)
		{
			image.createMaskFromColor(mask);
		}

		this->textures.insert(std::pair<std::string, sf::Texture>(key, sf::Texture()));
		this->textures[key].loadFromImage(image);
		this->textures[key].setSmooth(true);

	}
	return this->textures[key];

}