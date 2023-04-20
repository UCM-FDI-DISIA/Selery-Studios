#pragma once
#include "../utils/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/ecs.h"
#include "Transform.h"
#include "../utils/Constants.h"
#include "AttackBoxComponent.h"
#include "FramedImage.h"
#include "LifeBasicComponent.h"
#include "../sdlutils/SoundEffect.h"

class BeatEmUpState;

class FireBossComponent : public Component {
protected:
	
	Vector2D initial_posotion,player_pos;
	Entity* player;
	Transform* trans_player; 
	Transform*  my_transform;
	AttackBoxComponent* ttt;
	
	float velocity_x;
	float velocity_y;
	int current_time, maxtime;


	FramedImage* image;


	vector<Entity*> fire_colums;
	FramedImage* column_image;
	bool sevfive;
	Transform* trans_column;
	Vector2D column1 = { 400,400 };
	Vector2D column2 = { 200,400 };
	Vector2D column3 = { 100,400 };

	bool end = true;
	
	enum states{ moving_towards_player, moving_towards_initialpoint, attack, recovery, paused};
	states current = moving_towards_player;
	Texture* backTexture= &SDLUtils::instance()->images().at("Fire_LifeBarBack");
	Texture* LifeBarTexture= &SDLUtils::instance()->images().at("Fire_LifeBar");
	Texture* borderTexture = &SDLUtils::instance()->images().at("Fire_LifeBarBorder");
	int scale = WIN_WIDTH / 900;
	int barWidth_, backWidth_, borderWidth_, barHeight_, backHeight_, borderHeight_;


	float maxLife_=8000, current_life=maxLife_;
	int diff = 0;

	bool canSummonEnemies = true;
	bool canfire = true;
	bool canfire2 = true;
	int n = 0;

	const static int nEnemies = 3;
	LifeComponent* enemyRef[nEnemies];
	const char* const enemyTypes[4]{ "bat" ,"shroom" ,"goblin" ,"skeleton" };

	SoundEffect* death = &SDLUtils::instance()->soundEffects().at("fireboss_death");
	SoundEffect* hit = &SDLUtils::instance()->soundEffects().at("fire_golpe");
	SoundEffect* vanish = &SDLUtils::instance()->soundEffects().at("vanish");


	
	
public:	
	FireBossComponent(Entity* player);
	~FireBossComponent();
	virtual void initComponent();
	virtual void update();
	virtual void render();

	void summonEnemies(int n);
	void moveOutOfScreen();
	void subLife(float dmg);
	void moreLife();
	void createColumns(Vector2D p);
};

