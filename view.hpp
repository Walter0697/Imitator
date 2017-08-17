#pragma once

#include "model.hpp"
#include "manager.hpp"
#include "hud.hpp"
#include "enemyHud.hpp"

#include "Mode/menu.hpp"

#include "renderable.hpp"
#include "updateable.hpp"

#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 1000

class View {

public:

	Model* model;
	View(Model* model);
	~View();

	Hud* hud;
	EnemyHud* enemyhud;

	Menu* menu;
	sf::Sprite sprite_pause;

	Manager manager;
	sf::RenderWindow window;
	std::vector<Renderable *> renderables;
	std::vector<Renderable *> foreground;

	void renderStory();
	void renderMenu();
	void render();

	bool viewHitBox = false;
};