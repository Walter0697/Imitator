#include "view.hpp"
#include <iostream>
using namespace std;

View::View(Model* model)
{
	this->model = model;

	this->window.create(sf::VideoMode(WIDTH, HEIGHT), "Imitator(DEMO)");
	this->window.setFramerateLimit(60);
	this->window.setMouseCursorVisible(false);

	//loading menu
	this->menu = new Menu();
	this->menu->menuplayer.setTexture(manager.get_texture("Assets/menuplane.png", sf::Color(0, 128, 192)), true);
	if (!this->menu->font.loadFromFile("Assets/neuropolitical rg.ttf")) cout << "failed to load font neuropolitical rg.ttf" << endl;
	if (!this->menu->font2.loadFromFile("Assets/Crom_v1.ttf")) cout << "failed to load font Crom_v1.ttf" << endl;
	this->menu->setup();

	//loading story font
	if (!this->model->story->fontFriend.loadFromFile("Assets/huxtable.ttf")) cout << "failed to load font huxtable.ttf" << endl;
	if (!this->model->story->fontEnemy.loadFromFile("Assets/Somerset Barnyard.otf")) cout << "failed to load Somerset Barnyard.otf" << endl;
	if (!this->model->story->fontVictory.loadFromFile("Assets/neuropolitical rg.ttf")) cout << "failed to load font neuropolitical rg.ttf" << endl;
	if (!this->model->story->fontEnemy2.loadFromFile("Assets/Dog Rough.otf")) cout << "failed to load Dog Rough.otf" << endl;
	if (!this->model->story->fontFriend2.loadFromFile("Assets/blackthorns-black.ttf")) cout << "failed to load font blackthorns-black .ttf" << endl;
	if (!this->model->story->fontUnknown.loadFromFile("Assets/WINGDNG3.TTF")) cout << "failed to load font WINGDNG3.TTF" << endl;
	this->model->story->setup();

	//loading hud
	//player hud
	this->hud = new Hud(this->model->player);
	this->hud->healthBar.setTexture(manager.get_texture("Assets/EmptyBar.png", sf::Color(203, 112, 218)), true);
	this->hud->healthSize = manager.get_texture("Assets/EmptyBar.png").getSize();
	this->hud->setup();

	this->hud->health.setTexture(manager.get_texture("Assets/health.png", sf::Color(203, 112, 218)), true);
	this->hud->shield.setTexture(manager.get_texture("Assets/shield.png", sf::Color(203, 112, 218)), true);

	if (!this->hud->font.loadFromFile("Assets/hemi head bd it.ttf")) cout << "failed to load font hemi head bh it.ttf" << endl;

	//enemy hud
	this->enemyhud = new EnemyHud(this->model->enemySet);
	this->enemyhud->healthBar.setTexture(manager.get_texture("Assets/enemyEmptyBar.png", sf::Color(203, 112, 218)), true);
	this->enemyhud->healthSize = manager.get_texture("Assets/enemyEmptyBar.png").getSize();
	this->enemyhud->setup();

	this->enemyhud->health.setTexture(manager.get_texture("Assets/enemyHealth.png", sf::Color(203, 112, 218)), true);

	//loading pausing screen
	this->sprite_pause.setTexture(manager.get_texture("Assets/pause.png", sf::Color::White), true);
	this->sprite_pause.setPosition(SCREEN_WIDTH / 2 - manager.get_texture("Assets/pause.png").getSize().x / 2,
		SCREEN_HEIGHT / 2 - manager.get_texture("Assets/pause.png").getSize().y / 2);

	//loading mouse texture
	this->mouse_position = sf::Vector2f(0, 0);
	this->sprite_mouse.setTexture(manager.get_texture("Assets/cursor.png"), true);
	this->sprite_mouse.setPosition(mouse_position);

	//loading story sprite
	this->model->story->sprite[0].setTexture(manager.get_texture("Assets/pointer.png", sf::Color(237, 28, 36)), true);
	this->model->story->sprite[0].setPosition(99999, 99999);
	this->model->story->sprite[1].setTexture(manager.get_texture("Assets/shieldUnlock.png", sf::Color::White), true);
	this->model->story->sprite[1].setPosition(99999, 99999);
	this->model->story->sprite[2].setTexture(manager.get_texture("Assets/healthUnlock.png", sf::Color::White), true);
	this->model->story->sprite[2].setPosition(99999, 99999);
	this->model->story->sprite[3].setTexture(manager.get_texture("Assets/imumiumUnlock.png", sf::Color::White), true);
	this->model->story->sprite[3].setPosition(168, -30);
	this->model->story->sprite[4].setTexture(manager.get_texture("Assets/stoneUnlock.png", sf::Color::White), true);
	this->model->story->sprite[4].setPosition(168, -30);
	this->model->story->sprite_enter.setTexture(manager.get_texture("Assets/enter_key.png", sf::Color(51, 51, 51)), true);

	//setting up the record in hud
	if (!this->model->record->font.loadFromFile("Assets/hemi head bd it.ttf")) cout << "failed to load font hemi head bd it.ttf" << endl;
	this->model->record->scoreBoard.setTexture(manager.get_texture("Assets/scorePanel.png", sf::Color::White), true);
	this->model->record->scoreBoard.setPosition(0, 0);
	this->model->record->bullet_sprite[0].setTexture(manager.get_texture("Assets/default.png", sf::Color::White), true);
	this->model->record->bullet_sprite[1].setTexture(manager.get_texture("Assets/two-way.png", sf::Color::White), true);
	this->model->record->bullet_sprite[2].setTexture(manager.get_texture("Assets/long-shot.png", sf::Color::White), true);
	this->model->record->bullet_sprite[3].setTexture(manager.get_texture("Assets/shot-gun.png", sf::Color::White), true);
	this->model->record->bullet_sprite[4].setTexture(manager.get_texture("Assets/light-ball.png", sf::Color::White), true);
	this->model->record->bullet_sprite[5].setTexture(manager.get_texture("Assets/random-shot.png", sf::Color::White), true);
	this->model->record->bullet_sprite[6].setTexture(manager.get_texture("Assets/grenade-type.png", sf::Color::White), true);
	this->model->record->bullet_sprite[7].setTexture(manager.get_texture("Assets/fireshot.png", sf::Color::White), true);
	this->model->record->bullet_sprite[8].setTexture(manager.get_texture("Assets/lazer.png", sf::Color::White), true);
	this->model->record->bullet_sprite[9].setTexture(manager.get_texture("Assets/blast.png", sf::Color::White), true);
	this->model->record->bullet_sprite[10].setTexture(manager.get_texture("Assets/homing.png", sf::Color::White), true);
	this->model->record->bullet_sprite[11].setTexture(manager.get_texture("Assets/lazer_beam.png", sf::Color::White), true);
	this->model->record->bullet_sprite[12].setTexture(manager.get_texture("Assets/fire-work.png", sf::Color::White), true);
	this->model->record->bullet_sprite[13].setTexture(manager.get_texture("Assets/rocket-bullet.png", sf::Color::White), true);
	for (int i = 0; i < NUM_OF_BULLET; i++)
		this->model->record->bullet_sprite[i].setScale(sf::Vector2f(0.8f, 0.8f));
	this->model->record->setup();
	
	//setting up the bullet_type in hud
	this->hud->bullet_sprite[0].setTexture(manager.get_texture("Assets/default.png"), true);
	this->hud->bullet_sprite[1].setTexture(manager.get_texture("Assets/two-way.png"), true);
	this->hud->bullet_sprite[2].setTexture(manager.get_texture("Assets/long-shot.png"), true);
	this->hud->bullet_sprite[3].setTexture(manager.get_texture("Assets/shot-gun.png"), true);
	this->hud->bullet_sprite[4].setTexture(manager.get_texture("Assets/light-ball.png"), true);
	this->hud->bullet_sprite[5].setTexture(manager.get_texture("Assets/random-shot.png"), true);
	this->hud->bullet_sprite[6].setTexture(manager.get_texture("Assets/grenade-type.png"), true);
	this->hud->bullet_sprite[7].setTexture(manager.get_texture("Assets/fireshot.png"), true);
	this->hud->bullet_sprite[8].setTexture(manager.get_texture("Assets/lazer.png"), true);
	this->hud->bullet_sprite[9].setTexture(manager.get_texture("Assets/blast.png"), true);
	this->hud->bullet_sprite[10].setTexture(manager.get_texture("Assets/homing.png"), true);
	this->hud->bullet_sprite[11].setTexture(manager.get_texture("Assets/lazer_beam.png"), true);
	this->hud->bullet_sprite[12].setTexture(manager.get_texture("Assets/fire-work.png"), true);
	this->hud->bullet_sprite[13].setTexture(manager.get_texture("Assets/rocket-bullet.png"), true);
	
	//setting up the status_type in hud
	this->hud->status_sprite[0].setTexture(manager.get_texture("Assets/onFire.png", sf::Color(165, 165, 165)), true);
	this->hud->status_sprite[1].setTexture(manager.get_texture("Assets/onBuff.png", sf::Color::White), true);
	this->hud->status_sprite[2].setTexture(manager.get_texture("Assets/onLuck.png", sf::Color::White), true);

	//player texture
	this->model->player->sprite.setTexture(manager.get_texture("Assets/player.png", sf::Color(0, 128, 192)), true);
	this->model->player->size = manager.get_texture("Assets/player.png").getSize();
	this->model->player->sprite.setPosition(this->model->player->position);

	//enemy texture
	this->model->enemySet->sprite_denemy.setTexture(manager.get_texture("Assets/enemy.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_douenemy.setTexture(manager.get_texture("Assets/douddy.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_longenemy.setTexture(manager.get_texture("Assets/longgy.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_shotenemy.setTexture(manager.get_texture("Assets/shotty.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_gangenemy.setTexture(manager.get_texture("Assets/gangster.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_thugenemy.setTexture(manager.get_texture("Assets/thug.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_unknownenemy.setTexture(manager.get_texture("Assets/unknown.png", sf::Color::White), true);
	this->model->enemySet->sprite_glitchyenemy.setTexture(manager.get_texture("Assets/glitchy.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_advancedenemy.setTexture(manager.get_texture("Assets/advanced.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_lazzyenemy.setTexture(manager.get_texture("Assets/lazzy.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_friend.setTexture(manager.get_texture("Assets/friend.png", sf::Color(0, 128, 192)), true);

	//boss texture
	this->model->enemySet->sprite_devplane.setTexture(manager.get_texture("Assets/devPlane.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_devplane_ready.setTexture(manager.get_texture("Assets/devPlane-ready.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_modifier.setTexture(manager.get_texture("Assets/modifier.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_firethrower.setTexture(manager.get_texture("Assets/fireThrower.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_alien.setTexture(manager.get_texture("Assets/unknownboss.png", sf::Color::White), true);
	this->model->enemySet->sprite_labplane.setTexture(manager.get_texture("Assets/labShip.png", sf::Color(0, 128, 192)), true);
	this->model->enemySet->sprite_final.setTexture(manager.get_texture("Assets/finalBoss.png", sf::Color(0, 128, 192)), true);

	//player bullet texture
	this->model->playerSet->sprite_dbullet.setTexture(manager.get_texture("Assets/pbullet.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_dbullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/pbullet.png").getSize()) / 2.f);
	this->model->playerSet->sprite_twbullet_left.setTexture(manager.get_texture("Assets/p_two_way_left.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_twbullet_left.setOrigin(sf::Vector2f(manager.get_texture("Assets/p_two_way_left.png").getSize()) / 2.f);
	this->model->playerSet->sprite_twbullet_right.setTexture(manager.get_texture("Assets/p_two_way_right.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_twbullet_right.setOrigin(sf::Vector2f(manager.get_texture("Assets/p_two_way_right.png").getSize()) / 2.f);
	this->model->playerSet->sprite_longbullet.setTexture(manager.get_texture("Assets/long_shot.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_shotbullet.setTexture(manager.get_texture("Assets/shot_gun.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_shotbullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/shot_gun.png").getSize()) / 2.f);
	this->model->playerSet->sprite_lightball.setTexture(manager.get_texture("Assets/lightball.png", sf::Color::Black), true);
	this->model->playerSet->sprite_lightball.setOrigin(sf::Vector2f(manager.get_texture("Assets/lightball.png").getSize()) / 2.f);
	this->model->playerSet->sprite_randombullet.setTexture(manager.get_texture("Assets/randomshot.png", sf::Color(0, 0, 0)), true);
	this->model->playerSet->sprite_randombullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/randomshot.png").getSize()) / 2.f);
	this->model->playerSet->sprite_grenadebullet.setTexture(manager.get_texture("Assets/grenade.png", sf::Color::White), true);
	this->model->playerSet->sprite_grenadebullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/grenade.png").getSize()) / 2.f);
	this->model->playerSet->sprite_explosion.setTexture(manager.get_texture("Assets/explosion.png", sf::Color::Black), true);
	this->model->playerSet->sprite_explosion.setOrigin(sf::Vector2f(manager.get_texture("Assets/explosion.png").getSize()) / 2.f);
	this->model->playerSet->sprite_fireball.setTexture(manager.get_texture("Assets/fireball.png", sf::Color::White), true);
	this->model->playerSet->sprite_lazer.setTexture(manager.get_texture("Assets/lazer-shot.png", sf::Color::White), true);
	this->model->playerSet->sprite_blastshot.setTexture(manager.get_texture("Assets/blast-shot.png", sf::Color::Black), true);
	this->model->playerSet->sprite_blastshot.setOrigin(sf::Vector2f(manager.get_texture("Assets/blast-shot.png").getSize()) / 2.f);
	this->model->playerSet->sprite_homingshot.setTexture(manager.get_texture("Assets/homing-bullet.png", sf::Color::Black), true);
	this->model->playerSet->sprite_homingshot.setOrigin(sf::Vector2f(manager.get_texture("Assets/homing-bullet.png").getSize()) / 2.f);
	this->model->playerSet->sprite_lazerbeam.setTexture(manager.get_texture("Assets/lazer-beam.png", sf::Color::White), true);
	this->model->playerSet->sprite_fireroot.setTexture(manager.get_texture("Assets/fireworkRoot.png", sf::Color::Black), true);
	this->model->playerSet->sprite_fireroot.setOrigin(sf::Vector2f(manager.get_texture("Assets/fireworkRoot.png").getSize()) / 2.f);
	this->model->playerSet->sprite_firework.setTexture(manager.get_texture("Assets/firework.png", sf::Color::Black), true);
	this->model->playerSet->sprite_firework.setOrigin(sf::Vector2f(manager.get_texture("Assets/firework.png").getSize()) / 2.f);
	this->model->playerSet->sprite_rocket.setTexture(manager.get_texture("Assets/rocket.png", sf::Color::White), true);
	//enemy bullet texture
	this->model->enemyBulletSet->sprite_dbullet.setTexture(manager.get_texture("Assets/ebullet.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_dbullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/ebullet.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_twbullet_left.setTexture(manager.get_texture("Assets/p_two_way_right.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_twbullet_left.setOrigin(sf::Vector2f(manager.get_texture("Assets/p_two_Way_right.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_twbullet_right.setTexture(manager.get_texture("Assets/p_two_Way_left.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_twbullet_right.setOrigin(sf::Vector2f(manager.get_texture("Assets/p_two_way_left.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_longbullet.setTexture(manager.get_texture("Assets/long_shot.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_shotbullet.setTexture(manager.get_texture("Assets/shot_gun.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_shotbullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/shot_gun.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_lightball.setTexture(manager.get_texture("Assets/lightball.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_lightball.setOrigin(sf::Vector2f(manager.get_texture("Assets/lightball.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_randombullet.setTexture(manager.get_texture("Assets/randomshot.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_randombullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/randomshot.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_grenadebullet.setTexture(manager.get_texture("Assets/e_grenade.png", sf::Color::White), true);
	this->model->enemyBulletSet->sprite_grenadebullet.setOrigin(sf::Vector2f(manager.get_texture("Assets/e_grenade.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_explosion.setTexture(manager.get_texture("Assets/explosion.png", sf::Color(0, 0, 0)), true);
	this->model->enemyBulletSet->sprite_explosion.setOrigin(sf::Vector2f(manager.get_texture("Assets/explosion.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_fireball.setTexture(manager.get_texture("Assets/e_fireball.png", sf::Color::White), true);
	this->model->enemyBulletSet->sprite_lazer.setTexture(manager.get_texture("Assets/lazer-shot.png", sf::Color::White), true);
	this->model->enemyBulletSet->sprite_blastshot.setTexture(manager.get_texture("Assets/blast-shot.png", sf::Color::Black), true);
	this->model->enemyBulletSet->sprite_blastshot.setOrigin(sf::Vector2f(manager.get_texture("Assets/blast-shot.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_homingshot.setTexture(manager.get_texture("Assets/homing-bullet.png", sf::Color::Black), true);
	this->model->enemyBulletSet->sprite_homingshot.setOrigin(sf::Vector2f(manager.get_texture("Assets/homing-bullet.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_lazerbeam.setTexture(manager.get_texture("Assets/e-lazer-beam.png", sf::Color::White), true);
	this->model->enemyBulletSet->sprite_fireroot.setTexture(manager.get_texture("Assets/fireworkRoot.png", sf::Color::Black), true);
	this->model->enemyBulletSet->sprite_fireroot.setOrigin(sf::Vector2f(manager.get_texture("Assets/fireworkRoot.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_firework.setTexture(manager.get_texture("Assets/firework.png", sf::Color::Black), true);
	this->model->enemyBulletSet->sprite_firework.setOrigin(sf::Vector2f(manager.get_texture("Assets/firework.png").getSize()) / 2.f);
	this->model->enemyBulletSet->sprite_rocket.setTexture(manager.get_texture("Assets/e-rocket.png", sf::Color::White), true);

	//tool texture
	this->model->toolSet->sprite_greenShield.setTexture(manager.get_texture("Assets/greenShield.png", sf::Color::White), true);
	this->model->toolSet->sprite_greenShield.setOrigin(sf::Vector2f(11, 13));
	this->model->toolSet->sprite_blueShield.setTexture(manager.get_texture("Assets/blueShield.png", sf::Color::White), true);
	this->model->toolSet->sprite_blueShield.setOrigin(sf::Vector2f(11, 13));
	this->model->toolSet->sprite_yellowShield.setTexture(manager.get_texture("Assets/yellowShield.png", sf::Color::White), true);
	this->model->toolSet->sprite_yellowShield.setOrigin(sf::Vector2f(11, 13));
	this->model->toolSet->sprite_healthPack.setTexture(manager.get_texture("Assets/healthPack.png", sf::Color::White), true);
	this->model->toolSet->sprite_healthPack.setOrigin(sf::Vector2f(11, 13)); 
	this->model->toolSet->sprite_imumium.setTexture(manager.get_texture("Assets/holdbullet.png", sf::Color::White), true);
	this->model->toolSet->sprite_imumium.setOrigin(sf::Vector2f(12, 13));
	this->model->toolSet->sprite_stone.setTexture(manager.get_texture("Assets/lucky.png", sf::Color::White), true);
	this->model->toolSet->sprite_stone.setOrigin(sf::Vector2f(13, 13));
}

View::~View() {}

void View::renderReward()
{
	menu->render(this->window);
	model->story->sprite_enter.setPosition(522, 684);
	switch (model->reward_type)
	{
	case 1:
		window.draw(model->story->sprite[3]);
		break;
	case 2:
		window.draw(model->story->sprite[4]);
		break;
	}
	if (model->timer <= 0)
	{
		window.draw(model->story->sprite_enter);
	}
}

void View::renderStory()
{
	this->model->story->render(window);
}

void View::renderScore()
{
	this->model->record->render(scoreboard, window);
}

void View::renderMouse()
{
	sprite_mouse.setPosition(mouse_position);
	window.draw(sprite_mouse);
}

void View::renderMenu()
{
	if (this->model->gamemode == MODE_MENU_SCREEN)
		menu->render(this->window);
	else if (this->model->gamemode == MODE_GAME_OVER)
		menu->renderGameOver(this->window);
}

void View::render()
{
	for (int i = 0; i < this->renderables.size(); i++)
	{
		renderables[i]->render(this->window);
	}

	//hitbox
	if (viewHitBox)
	{
		this->model->player->renderHitbox(this->window);
		this->model->playerSet->renderHitBox(this->window);
		this->model->enemySet->renderHitBox(this->window);
		this->model->enemyBulletSet->renderHitBox(this->window);
		this->model->shield->renderHitBox(this->window);
		this->model->toolSet->renderHitBox(this->window);
		this->model->radShield->renderHitBox(this->window);
	}

	//foreground
	for (int i = 0; i < this->foreground.size(); i++)
	{
		foreground[i]->render(this->window);
	}

	if (this->model->pause)
		this->window.draw(sprite_pause);
}