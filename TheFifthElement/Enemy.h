#pragma once
#include "utils/Entity.h"
#include "Transform.h"
#include "utils/ecs.h"
#include "sdlutils/Texture.h"
#include "RenderComponent.h"
#include "GameManager.h"
#include "CheckCollision.h"
#include "PlayerTD.h"
#include "LifeComponent.h"


class Enemy : public Entity
{
private:
	Vector2D EnemyPosition_{ 300,150 };
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

public:

	Enemy(GameManager* gm_) : Entity() {
		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, EnemyPosition_, EnemyVelocity_, EnemyWidth_, EnemyHeight_, EnemyRotation_);
		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC5-idle-left.png");
		cmpId_type x = int(RENDERCOMPONENT_H);
		//referencia al texture y al transform
		addComponent<RenderComponent>(x, t, tr, nframes);
		//addComponent(ecs::TRANSFORM_H, Transform(this, m, Vector2D(0, 0), Vector2D(0, 0), 1, 1, 1));

	}

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

		cmpId_type z = int(TRANSFORM_H);
		tr = addComponent<Transform>(z, EnemyPosition_, EnemyVelocity_, EnemyWidth_, EnemyHeight_, EnemyRotation_);

		t = new Texture(gm_->getRenderer(), "./assets/NPCs/NPC5-idle-left.png");
		
		player_ = player;
		trPlayer_ = player_->getComponent<Transform>(z);

		cmpId_type w = int(CHECKCOLLISION_H);
		ch = addComponent<CheckCollision>(w, player_,gm_);

		cmpId_type x = int(RENDERCOMPONENT_H);
		addComponent<RenderComponent>(x, t, tr, nframes);

		cmpId_type v = int(LIFECOMPONENT_H);
		addComponent<LifeComponent>(v, m, tr, maxLife_);
	}

};

