#pragma once

#include <SFML/Graphics.hpp>

class Manager
{

public:

	Manager();																					//constructor

	std::map<std::string, sf::Texture> textures;												//a map to store the string and the texture

	const sf::Texture & get_texture(std::string, sf::Color = sf::Color::Transparent);			//map the color and the put it inside a map

};