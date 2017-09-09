#pragma once

#include "updateable.hpp"
#include "renderable.hpp"

#include "Enemy/defaultEnemy.hpp"
#include "Enemy/douddy.hpp"
#include "Enemy/longgy.hpp"
#include "Enemy/shotty.hpp"
#include "Enemy/gangster.hpp"
#include "Enemy/thug.hpp"
#include "Enemy/unknown.hpp"
#include "Enemy/glitchy.hpp"
#include "Enemy/advanced.hpp"
#include "Enemy/lazzy.hpp"
#include "Enemy/friendShip.hpp"

#include "Boss/devPlane.hpp"
#include "Boss/modifier.hpp"
#include "Boss/firethrower.hpp"
#include "Boss/alienShip.hpp"
#include "Boss/labPlane.hpp"
#include "Boss/finalBoss.hpp"

#include "hitbox.hpp"

#include "SFML/Graphics.hpp"

#include "defs.h"

class EnemySet : public Updateable, public Renderable
{

public:
	EnemySet();
	~EnemySet();

	void render(sf::RenderWindow&);
	void renderHitBox(sf::RenderWindow&);
	void update(sf::Time);

	void initEnemy();
	bool checkOutOfBound(Enemy&);
	void pushBack(sf::Time);
	int avaliableEnemy(int);

	void spawn(int, int);
	void spawn(int);

	int isFreeze = 0;

	int current_boss;

	//enemy
	DefaultEnemy denemies[MAX_DENEMY];
	Douddy douenemies[MAX_DENEMY];
	Longgy lonenemies[MAX_DENEMY];
	Shotty shotenemies[MAX_DENEMY];
	Gangster gangenemies[MAX_DENEMY];
	Thug thugenemies[MAX_DENEMY];
	Unknown unknownenemies[MAX_DENEMY];
	Glitchy glitchyenemies[MAX_DENEMY];	
	Advanced advancedenemies[MAX_DENEMY];
	Lazzy lazzyenemies[MAX_DENEMY];
	FriendShip friendShips[MAX_DENEMY];

	Hitbox hb_denemy;
	Hitbox hb_douenemy;
	Hitbox hb_longenemy;
	Hitbox hb_shotenemy;
	Hitbox hb_gangenemy;
	Hitbox hb_thugenemy;
	Hitbox hb_unknownenemy;
	Hitbox hb_glitchyenemy;
	Hitbox hb_advancedenemy;
	Hitbox hb_lazzyenemy;
	Hitbox hb_friend;

	sf::Sprite sprite_denemy;
	sf::Sprite sprite_douenemy;
	sf::Sprite sprite_longenemy;
	sf::Sprite sprite_shotenemy;
	sf::Sprite sprite_gangenemy;
	sf::Sprite sprite_thugenemy;
	sf::Sprite sprite_unknownenemy;
	sf::Sprite sprite_glitchyenemy;
	sf::Sprite sprite_advancedenemy;
	sf::Sprite sprite_lazzyenemy;
	sf::Sprite sprite_friend;

	sf::Sprite sprite_denemy_onFire;
	sf::Sprite sprite_douenemy_onFire;
	sf::Sprite sprite_longenemy_onFire;
	sf::Sprite sprite_shotenemy_onFire;
	sf::Sprite sprite_gangenemy_onFire;
	sf::Sprite sprite_thugenemy_onFire;
	sf::Sprite sprite_unknownenemy_onFire;
	sf::Sprite sprite_glitchyenemy_onFire;
	sf::Sprite sprite_advancedenemy_onFire;
	sf::Sprite sprite_lazzyenemy_onFire;
	sf::Sprite sprite_friend_onFire;

	sf::Sprite sprite_denemy_stop;
	sf::Sprite sprite_douenemy_stop;
	sf::Sprite sprite_longenemy_stop;
	sf::Sprite sprite_shotenemy_stop;
	sf::Sprite sprite_gangenemy_stop;
	sf::Sprite sprite_thugenemy_stop;
	sf::Sprite sprite_unknownenemy_stop;
	sf::Sprite sprite_glitchyenemy_stop;
	sf::Sprite sprite_advancedenemy_stop;
	sf::Sprite sprite_lazzyenemy_stop;
	sf::Sprite sprite_friend_stop;

	//boss
	DevPlane boss_devplane;
	Hitbox hb_boss_devplane;
	sf::Sprite sprite_devplane;
	sf::Sprite sprite_devplane_onFire;
	sf::Sprite sprite_devplane_ready;
	sf::Sprite sprite_devplane_ready_onFire;
	sf::Sprite sprite_devplane_end;
	sf::Sprite sprite_devplane_stop;

	Modifier boss_modifier;
	Hitbox hb_boss_modifier;
	sf::Sprite sprite_modifier;
	sf::Sprite sprite_modifier_onFire;
	sf::Sprite sprite_modifier_end;
	sf::Sprite sprite_modifier_stop;

	FireThrower boss_firethrower;
	Hitbox hb_boss_firethrower;
	sf::Sprite sprite_firethrower;
	sf::Sprite sprite_firethrower_onFire;
	sf::Sprite sprite_firethrower_end;
	sf::Sprite sprite_firethrower_stop;

	AlienShip boss_alien;
	Hitbox hb_boss_alien;
	sf::Sprite sprite_alien;
	sf::Sprite sprite_alien_onFire;
	sf::Sprite sprite_alien_end;
	sf::Sprite sprite_alien_stop;

	LabPlane boss_labplane;
	Hitbox hb_boss_labplane;
	sf::Sprite sprite_labplane;
	sf::Sprite sprite_labplane_onFire;
	sf::Sprite sprite_labplane_end;
	sf::Sprite sprite_labplane_stop;

	FinalBoss boss_final;
	Hitbox hb_boss_final;
	sf::Sprite sprite_final;
	sf::Sprite sprite_final_onFire;
	sf::Sprite sprite_final_end;
	sf::Sprite sprite_final_stop;
};