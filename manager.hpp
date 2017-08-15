#pragma once

#include <SFML/Graphics.hpp>

class Manager
{

public:

	Manager();

	std::map<std::string, sf::Texture> textures;

	const sf::Texture & get_texture(std::string, sf::Color = sf::Color::Transparent);

};