#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerTD.h"
#include "LifeComponent.h"


class Enemy : public Entity
{
private:
	Vector2D EnemyPosition_{ 450,150 };
	Vector2D EnemyVelocity_{ 0,0 };
	float EnemyWidth_ = 476, EnemyHeight_ = 120, EnemyRotation_ = 1;
	Texture* t;
	Transform* tr;
	Transform* trPlayer_;
	GameManager* m;
	PlayerTD* player_;
	CheckCollision* ch;
	int nframes = 7;
	float life_, maxLife_;
	int w = 68;
	int h = 120;
public:



	~Enemy()
	{

	}

	void update()
	{
	
	}


	Enemy(GameManager* gm_, PlayerTD* player, float maxLife) : Entity()
	{
		maxLife_ = maxLife;
		life_ = maxLife;
		m = gm_;
		float a =1.0f;
		float lookingRange = 150.0f;
		float lookingWidth = 100.0f;
		tr = addComponent<Transform>(int(TRANSFORM_H), EnemyPosition_, EnemyVelocity_, EnemyWidth_, EnemyHeight_, EnemyRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC5-idle-left.png");
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(int(TRANSFORM_H));
		ch = addComponent<CheckCollision>(int(CHECKCOLLISION_H), player_,gm_);
		addComponent<Image>(int(IMAGE_H), t, nframes);
		addComponent<LifeBarComponent>(int(LIFEBARCOMPONENT_H), m, tr, maxLife_);
	}

};

