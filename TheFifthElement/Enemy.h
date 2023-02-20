#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/SDLUtils.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerTD.h"
#include "LifeComponent.h"
#include "./componets/Enemy_movementTD_component.h"


class Enemy : public Entity
{
private:
	Vector2D EnemyPosition_{ 700,150 };
	//float speed_ = 0.0f;
	float EnemyWidth_ = 476, EnemyHeight_ = 120, EnemyRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	GameManager* m;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 7;
	int fila_;
	float life_, maxLife_;
	bool matrix_ = false;
public:



	~Enemy()
	{

	}

	void update()
	{
		
	}


	Enemy(GameManager* gm_, PlayerTD* player, float maxLife) : Entity()
	{
		addComponent<Enemy_movementTD_component>(int(ENEMY_MOVEMENT_TD_H));
		maxLife_ = maxLife;
		life_ = maxLife;
		m = gm_;
		float a =-1.0f;
		float lookingRange = 150.0f;
		float lookingWidth = 100.0f;
		tr = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyWidth_, EnemyHeight_, EnemyRotation_, nframes, matrix_);
		t = &SDLUtils::instance()->images().at("TD_wind_mushroom");
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		//addComponent<LifeComponent>(int(LIFECOMPONENT_H), m, tr, maxLife_);
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_,gm_, lookingRange, lookingWidth, a);
		
		fila_ = 0;
		addComponent<Image>(int(IMAGE_H), t, nframes, nframes, fila_);
		
	}

};

