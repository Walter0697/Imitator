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

	Model* model;						//pointer of the model, MVC architecture
	View(Model* model);					//constructor
	~View();							//destructor

	Hud* hud;							//hud of the game
	EnemyHud* enemyhud;					//enemy hud of the game
	
	Menu* menu;							//menu of the game
	sf::Sprite sprite_pause;			//sprite for pausing

	sf::Sprite sprite_mouse;			//sprite for the mouse
	sf::Vector2f mouse_position;		//mouse position

	sf::Sprite control_board[2];		//control board

	Manager manager;					//image manager
	sf::RenderWindow window;			//renderwindow
	std::vector<Renderable *> renderables;	//renderable for foreground and background
	std::vector<Renderable *> foreground;
	
	void renderMouse();					//render method for different screen
	void renderReward();
	void renderStory();
	void renderMenu();
	void renderScore();
	void render();

	int scoreboard = 1;

	bool viewHitBox = false;
};